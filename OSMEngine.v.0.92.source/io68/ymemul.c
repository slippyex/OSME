/*
 *                         sc68 - YM-2149 emulator
 *           Copyright (C) 1999 Benjamin Gerard <ben@sashipa.com>
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by the
 *  Free Software Foundation; either version 2 of the License, or (at your
 *  option) any later version.
 *
 *  This program is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 */
#include <config68.h>
#include "io68/ymemul.h"

#define YM_MASTER_FRQ  2000000  /**< YM master frequency in Atari ST:2Mhz */
#define YM_FRQ         250000   /**< Max frequency involved (for envelop) */

#define MAX_SPL_PER_PASS (YM_FRQ / REPLAY_RATE_MIN)+1
#define MAX_VOLUME_ENTRY 4096
static int filter_cnt;

static s32 mixbuf[MAX_SPL_PER_PASS], * mixptr;
#if ATARI 

#if defined(DEBUG) && !defined(_DEBUG)
#define _DEBUG DEBUG
#endif

#if defined(_DEBUG) && !defined(DEBUG)
#define DEBUG _DEBUG
#endif

#ifdef DEBUG
#include <stdio.h> /*$$$ DEBUG TEMP */
#endif

/** Table of 5 bit D/A output level for 1 channel.
 */
static const u16 ymout1c5bit[] =
# include "io68/ymout1c5bit.h"

/** 3 channels output table.
 *    Using a table for non linear mixing.
 */
static u16 ymout5[32*32*32];

#define YM_OUT_MSK_A 0x001F
#define YM_OUT_MSK_B 0x03E0
#define YM_OUT_MSK_C 0x7c00

static const int ym_out_msk[3] = { 
 YM_OUT_MSK_A, YM_OUT_MSK_B, YM_OUT_MSK_C
};

#define YM_OUT_MSK(C,B,A) \
 (((((C)&0x1F)<<10))\
 |((((B)&0x1F)<< 5))\
 |((((A)&0x1F)    )))



#define INTMSB  ((sizeof(int)<<3)-1)

/* $$$ s32 ??? verify this */
static int envbuf[MAX_SPL_PER_PASS], * envptr;
static int noibuf[MAX_SPL_PER_PASS], * noiptr;

/* static int fake_cycle; */
/* static int output_level; */

static int hipass_inp1;
static int hipass_out1;
static int lopass_out1;

/* #ifdef _DEBUG */
/*   static int noiseCnt; */
/*   static int envCnt; */
/*   static int mixCnt; */
/* #endif */

static unsigned int voiceCut = YM_OUT_MSK(-1,-1,-1);

typedef struct
{
  int cycle;
  u8  reg,v;
} entry_t;

typedef struct
{
  int lc;                       /* Last cycle mixed.           */
  entry_t *c;                   /* Free entry.                 */
  entry_t e[MAX_VOLUME_ENTRY];  /* Static register entry list. */
} entrylist_t;

static entrylist_t envelopR, noiseR, mixerR;
static unsigned int ifrq = 0;

#if 0
static const struct filter_def_t {
  s64 A0,B0; /* A1 = -A0 */
} filter_def[8] =
{
  /* 0123456789ABCDEF     0123456789ABCDEF  cutoff/sampling */
  {0x0000ffb4522a469bLL,0x0000ff68a4548d37LL}, /* 23/62500 */
  {0x0000ff9a09ef0019LL,0x0000ff3413de0032LL}, /* 31/62500 */
  {0x0000ff72a7ba0de5LL,0x0000fee54f741bcbLL}, /* 43/62500 */
  {0x0000ff586d0271f6LL,0x0000feb0da04e3edLL}, /* 51/62500 */

  {0x0000ff94cbfc73a4LL,0x0000ff2997f8e748LL}, /* 23/44100 */
  {0x0000ff6f974da2b8LL,0x0000fedf2e9b4571LL}, /* 31/44100 */
  {0x0000ff37dc9e7a33LL,0x0000fe6fb93cf466LL}, /* 43/44100 */
  {0x0000ff12c309cd7aLL,0x0000fe2586139af5LL}  /* 51/44100 */
};
#endif

static const int smsk_table[8] = {
  /* 000 */ YM_OUT_MSK(00,00,00),
  /* 001 */ YM_OUT_MSK(00,00,-1),
  /* 010 */ YM_OUT_MSK(00,-1,00),
  /* 011 */ YM_OUT_MSK(00,-1,-1),
  /* 100 */ YM_OUT_MSK(-1,00,00),
  /* 101 */ YM_OUT_MSK(-1,00,-1),
  /* 110 */ YM_OUT_MSK(-1,-1,00),
  /* 111 */ YM_OUT_MSK(-1,-1,-1)
};

/* $$$ ARG this is exported with such a common name :( */
ym2149_t ym;

static void reset_entry(entrylist_t *l)
{
  l->lc = 0;
  l->c  = l->e;
}

static void add_entry(entrylist_t *l, u32 reg, u32 v, u32 cycle)
{
  entry_t * p = l->e+MAX_VOLUME_ENTRY;

  if (l->c != p) {
    p = l->c++;
  } else {
    p--;
    BREAKPOINT68;//("add_entry overflow");
  }
  p->cycle = cycle;
  p->reg   = reg;
  p->v     = v;
}

static int get_entry(entrylist_t *l, int reg, int cycle)
{
  entry_t *p;

  /* Found last minus cycle in write list */
  for (p = l->c-1; p >= l->e; --p) {
    if (p->reg==reg) return p->v;
  }

  /* Not found : Get local */
  return ym.data[reg];
}

static void subcycle_entry(entrylist_t *l, unsigned int subcycle)
{
  entry_t *p;
  l->lc -= subcycle;

#ifdef _DEBUG
  if ((int) l->lc) {
    BREAKPOINT68;
    l->lc = 0;
  }

  if ((int) l->lc < 0) {
    BREAKPOINT68;
    l->lc = 0;
  }
#endif

  for (p = l->e; p < l->c; ++p) {
    p->cycle -= subcycle;
#ifdef _DEBUG
    if ( (int)p->cycle < 0) {
      BREAKPOINT68;
      p->cycle = 0;
    }
#endif
  }
}

/******************************************************
*                  Set replay frequency               *
******************************************************/
int YM_sampling_rate(int f)
{
  if (f > 0) {
    ifrq =
      (f < SAMPLING_RATE_MIN)
      ? SAMPLING_RATE_MIN
      : ((f > SAMPLING_RATE_MAX)
	 ? SAMPLING_RATE_MAX
	 : f);
  }
  return ifrq;
}

/******************************************************
*                  Yamaha reset                       *
******************************************************/

/* shape format : [CONTinue | ATTack | ALTernate | HOLD] */
static void set_env_shape(int shape)
{
  /* Alternate mask start value depend on ATTack bit */
  ym.env_alt    = (~((shape << (INTMSB-2)) >> INTMSB)) & 0x1F;
  ym.env_bit    = 0;
  ym.env_bitstp = 1;
  ym.env_cont   = 0x1f;

  /* $$$ Not sure, that this counter is resetted, but it seems 
         cleaner. */
   ym.env_ct = 0;

  // $$$ TEMP !
  //ym.env_ct = 0x10000; 

  /* $$$ temp */
  //ym.data[YM_ENVTYPE] = shape;
}

int YM_reset(void)
{
  int i;
  for (i=0; i<sizeof(ym.data); i++) {
    ym.data[i]=0;
  }
  ym.data[YM_MIXER]   = 077;
  ym.data[YM_ENVTYPE] = 0x0a;
  ym.ctrl             = 0;
  ym.env_ct           = 0;

  ym.noise_gen        = 1;
  ym.noise_ct         = 0;

  ym.voice_ctA        = 0;
  ym.voice_ctB        = 0;
  ym.voice_ctC        = 0;
  ym.sq               = 0;
  reset_entry(&mixerR);
  reset_entry(&noiseR);
  reset_entry(&envelopR);
  set_env_shape(ym.data[YM_ENVTYPE]);

  hipass_inp1 = 0;
  hipass_out1 = 0;
  lopass_out1 = 0;

  filter_cnt   = 0;


/*   filter_acu = 0; */
/*   filter_v   = 0; */
/*   fake_cycle = 0; */

  /*voiceCut = 0xFFF;*/ /* Do not reset voice cut */
  return 0;
}

/******************************************************
*                  Yamaha init                        *
******************************************************/


/*
 *
 */
static void create_5bit_linear_table(u16 * out, unsigned int level)
{
  int i;
  const unsigned int min = ymout1c5bit[31];
  const unsigned int max = ymout1c5bit[00];
  const unsigned int div = max-min;

/*   output_level = level; */

  for (i=0; i<32*32*32; ++i) {
    unsigned int tmp =
      (  (unsigned int)ymout1c5bit[31-((i>>10)&0x1F)] +
	 (unsigned int)ymout1c5bit[31-((i>> 5)&0x1F)] +
	 (unsigned int)ymout1c5bit[31-((i>> 0)&0x1F)] -
	 3u * min ) / 3u * level / div;
    u16 v = (u16) tmp;

#if _DEBUG
    if ( (unsigned int) v != tmp ) {
      BREAKPOINT68;
    }
#endif
    out[i] = v;
  }
}

#if 0
static void init_output_level(unsigned int new_level)
{
  int i;
  unsigned int mult = (new_level<<14)/(ymout[0xfff]+1);

  output_level = new_level;

  for(i=0; i<4096; i++) {
    unsigned int v;
    v = ((unsigned int)ymout[i] * mult) >> 14;
    if (v > new_level) {
#ifdef _DEBUG
      BREAKPOINT68;
#endif
      v = new_level;
    }
    ymout[i] = v;
  }
}
#endif

int YM_init(void)
{
  create_5bit_linear_table(ymout5,0xA000);
  //  init_output_level(0xD000);
  YM_reset();
  if (!ifrq) {
    YM_sampling_rate(SAMPLING_RATE_DEF);
  }
  return 0;
}

/******************************************************
*                  Noise generator                    *
******************************************************/

/*
 * Generate noise for ncycle ( 8Mhz )
 * - stp is step for this noise period
 * - msk is mixer mask for noise
 * - mix in noiptr & update it
 *
 * -> return # cycle not mixed
 *
 */

/** New version : one cycle emulation */
static int generate_noise(int ncycle)
{
  int rem_cycle;
  int v, noise_gen, ct, per, msk;
  int * b;

#ifdef _DEBUG
  if (ncycle < 0) {
    BREAKPOINT68;
    return 0;
  }
#endif

  rem_cycle = ncycle & 31;
  if(!(ncycle >>= 5)) return rem_cycle;

  /* All inits */
  ct        = ym.noise_ct;
  noise_gen = ym.noise_gen;
  per       = (ym.data[YM_NOISE] & 0x3F) << 1; //$$$ ???
  msk       = smsk_table[7 & (ym.data[YM_MIXER] >> 3)];
  b         = noiptr;
  v         = -(noise_gen & 1) | msk;
  do {
    if (++ct >= per) {
      ct = 0;

      /* --- Based on MAME :) --- */
      /* The Random Number Generator of the 8910 is a 17-bit shift */
      /* register. The input to the shift register is bit0 XOR bit2 */
      /* (bit0 is the output). */

      /* bit 17 := bit 0 ^ bit 2 */
      noise_gen |= ((noise_gen^(noise_gen>>2)) & 1)<<17;
      noise_gen >>= 1;
      v = -(noise_gen & 1) | msk;
    }
    *b++ = v;
  } while (--ncycle);

  /* Save value for next pass */
  noiptr = b;
  ym.noise_gen = noise_gen;
  ym.noise_ct = ct;

  /* return not mixed cycle */
  return rem_cycle;
}

static void cycle_noise_gen(int cycle)
{
  entry_t *p;
  unsigned int lastcycle;
  noiptr = noibuf;

#ifdef _DEBUG
  if (cycle < 0) {
    BREAKPOINT68;
    return;
  }
#endif

  if (!cycle) {
    return;
  }

  for (p=noiseR.e, lastcycle=noiseR.lc; p<noiseR.c; p++) {
    int ncycle;

    ncycle = p->cycle - lastcycle;
    if (ncycle) {
      lastcycle = p->cycle - generate_noise(ncycle);
    }
    ym.data[p->reg] = p->v;
  }
  lastcycle = cycle - generate_noise(cycle - lastcycle);

#ifdef _DEBUG
  if (lastcycle != cycle) {
    BREAKPOINT68;
  }
#endif

  noiseR.lc = lastcycle;
  noiseR.c  = noiseR.e;
}

/******************************************************
*                Envelop generator                    *
******************************************************/

static int generate_env(int ncycle)
{
  int rem_cycle;
  int *b;
  int ct, per;
  unsigned int bit, bitstp, restp;
  unsigned int cont, recont;
  unsigned int alt, altalt;
  int shape;

#ifdef _DEBUG
  if (ncycle < 0) {
    BREAKPOINT68;
    return 0;
  }
#endif

  rem_cycle = ncycle & 31;
  if(!(ncycle >>= 5)) return rem_cycle;

  b       = envptr;

  /* period */
  ct      = ym.env_ct;
  per     = ym.data[YM_ENVL] | (ym.data[YM_ENVH]<<8);
  per     |= !per;
  shape   = ym.data[YM_ENVTYPE];

  /* bit */
  bit     = ym.env_bit;
  bitstp  = ym.env_bitstp;
  restp   = (shape & 1) ^ 1;

  /* continue */
  cont    = ym.env_cont;
  recont  = (-((shape>>3) & 0x1)) & 0x1F;

  /* alternate */
  alt     = ym.env_alt;
  altalt  = (-((shape ^ (shape>>1)) & 0x1)) & 0x1F;

  do {
    int n;

    n = per - ct;
    if (n <= 0) {
      int prev_bit;
      ct = 0;
      n = per;
      prev_bit = bit;
      bit += bitstp;
      if ((bit^prev_bit) & 32) {
        bitstp = restp;
        cont = recont;
        alt ^= altalt;
      }
    }

    /* 5 bit version */
    int v = (bit ^ alt) & cont;
    v |= v<<5;
    v |= v<<5;

    if (n > ncycle) {
      n = ncycle;
    }
    ncycle -= n;
    ct += n;

#ifdef _DEBUG
    if (n<=0) {
      BREAKPOINT68;
      break;
    }
#endif

    do {
      *b++ = v;
    } while (--n);

  } while (ncycle);

  /* $$$  Must correct the env countr here */

/* #ifdef _DEBUG */
/*   envCnt += b-envptr; */
/* #endif */

  /* Save value for next pass */
  envptr        = b;
  ym.env_ct     = ct;
  ym.env_bit    = bit;
  ym.env_bitstp = bitstp;
  ym.env_cont   = cont;
  ym.env_alt    = alt;

  return rem_cycle;
}

static void cycle_env_gen(int cycle)
{
  entry_t *p, *pe;
  int lastcycle;

#ifdef _DEBUG
  if (cycle < 0) {
    BREAKPOINT68;
    return;
  }
#endif

  if (!cycle) {
    return;
  }

  envptr = envbuf;

  for (p=envelopR.e, pe=envelopR.c, lastcycle=envelopR.lc; p<pe; ++p) {
    int ncycle;

    ncycle = p->cycle - lastcycle;
    if (ncycle) {
      lastcycle =
	p->cycle - generate_env(ncycle);
    }

    ym.data[p->reg] = p->v;
    if(p->reg == YM_ENVTYPE) {
      set_env_shape(p->v);
    }
  }

  lastcycle = cycle -
    generate_env(cycle-lastcycle);

#ifdef _DEBUG
  if (lastcycle != cycle) {
    BREAKPOINT68;
  }
#endif

  envelopR.lc = lastcycle;
  envelopR.c  = envelopR.e;
}

/******************************************************
*                Sound generator                      *
******************************************************/

static int generate_mixer(int ncycle)
{
  const int center = ymout5[0x7FFF] >> 1;

  int ctA,  ctB,  ctC;
  int perA, perB, perC;
  int smsk, emsk, vols;

  s32 * b;
  int * e, * o;
  int rem_cycle, v;
  int levels;

#ifdef _DEBUG
  if (ncycle < 0) {
    BREAKPOINT68;
    return 0;
  }
#endif

  /* Not enought cycle !!! */
  rem_cycle = ncycle & 31;
  ncycle >>= 5;
  if(!ncycle) {
    return rem_cycle;
  }

  /* init buffer address */
  o = noiptr;
  e = envptr;
  b = mixptr;

  smsk = smsk_table[7 & ym.data[YM_MIXER]];

  /* 3 voices buzz or lvl mask */
  emsk = vols = 0;

  v = ym.data[YM_VOL(0)] & 0x1F;
  if(v&0x10) emsk |= YM_OUT_MSK_A;
  else       vols |= (v<<1)+1;

  v = ym.data[YM_VOL(1)]&0x1F;
  if(v&0x10) emsk |= YM_OUT_MSK_B;
  else       vols |= (v<<6)+(1<<5);

  v = ym.data[YM_VOL(2)]&0x1F;
  if(v&0x10) emsk |= YM_OUT_MSK_C;
  else       vols |= (v<<11)+(1<<10);

  /* Mixer steps & couters */
  ctA = ym.voice_ctA;
  ctB = ym.voice_ctB;
  ctC = ym.voice_ctC;

  perA = ym.data[YM_PERL(0)] | ((ym.data[YM_PERH(0)]&0xF)<<8);
/*   perA |= !perA; */
  perB = ym.data[YM_PERL(1)] | ((ym.data[YM_PERH(1)]&0xF)<<8);
/*   perB |= !perB; */
  perC = ym.data[YM_PERL(2)] | ((ym.data[YM_PERH(2)]&0xF)<<8);
/*   perC |= !perC; */

  levels = ym.sq;
  do {
    int sq;

    sq = -(++ctA >= perA);
    levels ^= YM_OUT_MSK_A & sq;
    ctA &= ~sq;

    sq = -(++ctB >= perB);
    levels ^= YM_OUT_MSK_B & sq;
    ctB &= ~sq;

    sq = -(++ctC >= perC);
    levels ^= YM_OUT_MSK_C & sq;
    ctC &= ~sq;

    sq = levels;
    sq |= smsk;
    sq &= *o++;
    sq &= ((*e++)&emsk) | vols;
    
    sq &= voiceCut;
    sq = (int)ymout5[sq];
    sq -= center;
    
    *b++ = sq;
  
  } while (--ncycle);

  /* $$$ Add error correction here  */

/* #ifdef _DEBUG */
/*   mixCnt += b-mixptr; */
/* #endif */

  /* Save value for next pass */
  ym.voice_ctA = ctA;
  ym.voice_ctB = ctB;
  ym.voice_ctC = ctC;
  ym.sq        = levels;
  noiptr       = o;
  envptr       = e;
  mixptr       = b;

  return rem_cycle;
}


static void cycle_mix_gen(int cycle)
{
  entry_t *p;
  unsigned int lastcycle;

  mixptr = mixbuf + filter_cnt;
  envptr = envbuf;
  noiptr = noibuf;

  for (p=mixerR.e, lastcycle=mixerR.lc; p<mixerR.c;) {
    int ncycle, ccycle;

    ccycle = p->cycle;
    ncycle = ccycle - lastcycle;
    
    if (ncycle) {
      lastcycle =
	ccycle - generate_mixer(ncycle);
    }
    do {
      ym.data[p->reg] = p->v;
      p++;
    } while (p<mixerR.c && p->cycle == ccycle);

  }

  lastcycle =
    cycle - generate_mixer(cycle-lastcycle);
  
#ifdef _DEBUG
  if (lastcycle != cycle) {
    BREAKPOINT68;
  }
#endif

  mixerR.lc = lastcycle;
  mixerR.c = mixerR.e;
}

/* Transform 250000Hz buffer to current sampling rate.
 *
 * In order to emulate envelop tone half level trick, 
 * the function works by block of 4 PCM which are
 * averaged. Since number of PCM in source buffer may not be
 * a multiple of 4, the funcion uses a filter accumulator.
 */
static void filter(void)
{
  int n;
  s32 * src, * dst;

  /* Number of sample @ 250Khz */
  n = mixptr - mixbuf;

/*   fprintf(stderr,"filter: n-in=%d filter_cnt=%d\n",n,filter_cnt); */

  if (n <= 0) {
    return;
  }

#if _DEBUG
  if (n&3) {
    fprintf(stderr,"filter cycle=%d,count=%d\n",n,n&3);
    BREAKPOINT68;
  }
#endif

  src = mixbuf;
  dst = src + (filter_cnt = n&3);
  n >>= 2; /* Number of block */

  if (n > 0) {

    int h_i1 = hipass_inp1;
    int h_o1 = hipass_out1;
    int l_o1 = lopass_out1;
    int m = n;

    do {
      int i0,o0;

      /* Empirical filter from 250Khz to 62.5Khz.
       * It allow to emulate half level buzz sounds.
       */
      i0  = *src++;
      i0 += *src++; i0 += *src++; i0 += *src++;
      i0 >>= 2; /* i0 => 16bit */

      if (0) {
	o0 = i0;
	goto store;
      }

      /*
       * Recursive single pole lowpass filter.
       *
       * Harcoded for a 22.5Khz cutoff frequency with a 62.5Kz sampling rate.
       *
       *   o[N] = i[N] * A + output[N-1] * B
       *
       *   X = exp(-2.0 * pi * Fc)
       *   A = 1 - X = 1 - B
       *   B = X
       *   Fc = cutoff freq / sample rate
       *
       */
      {
	const int B = 0x0DF2A3a9; /* 31 bit */
	const int A = 0x720d5c57; /* 31 bit */

	s64 tmp0 =
	  ((i0<<15) * (s64) A) + 
	  (l_o1 * (s64) B);       /* tmp0 => 62 bit */
	l_o1 = tmp0>>31;
	/* i0 => 31 bit */
      }

      /* Recursive single pole high-pass filter
       *
       * Harcoded for a 23Hz cutoff with a 62.5Kz sampling rate.
       *
       *   o[N] = A0 * i[N] + A1 * i[N-1] + B1 * o[N-1]
       *        = A0 * i[N] - A0 * i[N-1] + B1 * o[N-1]
       *        = A0 * ( i[N] - i[N-1] )  + B1 * o[N-1]
       *   X  = exp(-2.0 * pi * Fc)
       *   A0 = (1 + X) / 2
       *   A1 = -(1 + X) / 2 = -A0
       *   B1 = X
       *   Fc = cutoff freq / sample rate
       *
       */
      {
	const int A0 = 0x7FDA2915; /* 31 bit */
	const int B1 = 0x7FB4522A; /* 31 bit */

	s64 tmp0 =
	  ((l_o1 - h_i1) * (s64) A0) +
	  (h_o1 * (s64) B1);
	h_i1 = l_o1;
	h_o1 = tmp0 >> 31;
	o0 = h_o1 >> 15;

#ifdef DEBUG
	if (1) {
	  static int max=0, min=0;
	  
	  if (o0 < min) {
	    min = o0;
	    fprintf(stderr,"min:%d ",o0);
	  }
	  if (o0 > max) {
	    max = o0;
	    fprintf(stderr,"max:%d ",o0);
	  }
	}
#endif

	if (o0 < -32768) {
#ifdef DEBUG
	  fprintf(stderr,"sat:%d ",o0);
#endif
	  o0 = -32768;
	} else if (o0 > 32767) {
#ifdef DEBUG
	  fprintf(stderr,"sat:%d ",o0);
#endif
	  o0 = 32767;
	}

      }

    store:
      *dst++ = o0;

    } while (--m);

    hipass_inp1 =  h_i1;
    hipass_out1 =  h_o1;
    lopass_out1 =  l_o1;

    /* Copy remaining sample in the beginning of buffer. */
    dst = mixbuf;
    if (filter_cnt & 1) { *dst++ = *src++; }
    if (filter_cnt & 2) { *dst++ = *src++; *dst++ = *src++; }
    src = dst;

    unsigned int stp, ct, end;
    ct  = 0;
    stp = (YM_FRQ << 14) / ifrq;
    end = n << 16;

    do {
      *dst++ = src[ct>>16];
    } while ((ct += stp) < end);

  }
  mixptr = dst;
}

/******************************************************
*                  Yamaha process                     *
*               return # mixed sample                 *
******************************************************/
int YM_mix(cycle68_t cycle2mix)
{
  /* $$$ Must check buffer overflow here */

#ifdef _DEBUG
  if (cycle2mix&31) {
    BREAKPOINT68;
  }
#endif
/*   cycle2mix += fake_cycle; */
/*   fake_cycle = cycle2mix&31; */
/*   cycle2mix -= fake_cycle; */
  

/* #ifdef _DEBUG */
/*   mixCnt = noiseCnt = envCnt = 0; */
/* #endif */

#ifdef _DEBUG
  if (envelopR.lc != noiseR.lc || envelopR.lc != mixerR.lc) {
    BREAKPOINT68;
  }
#endif

  /* $$$macosx */
/*   fprintf(stderr, "ENTER YM_mix %d\n", cycle2mix); */
  
  cycle_noise_gen(cycle2mix);
  cycle_env_gen(cycle2mix);
  cycle_mix_gen(cycle2mix);

/* #ifdef _DEBUG */
/*   /\* $$$ Should not happen *\/ */
/*   if (mixCnt != noiseCnt || mixCnt != envCnt) { */
/*     BREAKPOINT68; */
/*   } */
/* #endif */

  mixerR.lc = envelopR.lc = noiseR.lc = cycle2mix/* + fake_cycle */;

/*   fprintf(stderr, "filter\n"); */
  filter();
/*   fprintf(stderr, "-> count=%d\n",mixptr - mixbuf); */
  return mixptr - mixbuf - filter_cnt;
}

/*************************************
*         Write in YM register       *
*************************************/
void YM_writereg(u8 reg, u8 v, cycle68_t cycle)
{
  switch(reg)
  {
    case YM_PERL(0): case YM_PERH(0):
    case YM_PERL(1): case YM_PERH(1):
    case YM_PERL(2): case YM_PERH(2):
    case YM_VOL(0): case YM_VOL(1): case YM_VOL(2):
      add_entry( &mixerR, reg, v,  cycle );
      break;

    case YM_ENVL: case YM_ENVH: case YM_ENVTYPE:
      add_entry( &envelopR, reg, v, cycle );
      break;

    case YM_MIXER: /* Reg 7 modify both noise gen & mixer */
      add_entry( &mixerR, reg, v, cycle );
    case YM_NOISE:
      add_entry( &noiseR, reg, v, cycle );
      break;

    default:
      break;
  }
}

/********************************************
*         Read from YM register             *
********************************************/
u8 YM_readreg(u8 reg, cycle68_t cycle)
{
  switch(reg)
  {
    case YM_PERL(0): case YM_PERH(0):
    case YM_PERL(1): case YM_PERH(1):
    case YM_PERL(2): case YM_PERH(2):
    case YM_VOL(0): case YM_VOL(1): case YM_VOL(2):
      return get_entry( &mixerR, reg, cycle );

    case YM_ENVL: case YM_ENVH: case YM_ENVTYPE:
      return get_entry( &envelopR, reg, cycle );

    case YM_NOISE:
    case YM_MIXER:
      /* Reg 7 is used in 2 lists */
      /* Better choice is noise   */
      return get_entry( &noiseR, reg, cycle );

    default:
      break;
  }
  return 0;
}

/****************************************** *
*         Change YM cycle count base        *
********************************************/
void YM_subcycle(cycle68_t subcycle)
{
  subcycle_entry(&mixerR,   subcycle);
  subcycle_entry(&envelopR, subcycle);
  subcycle_entry(&noiseR,   subcycle);
}


/******************************************************
*                 Yamaha get activated voices         *
******************************************************/
int YM_get_activevoices(void)
{
  return (voiceCut&1) | ((voiceCut>>5)&2) | ((voiceCut>>10)&4);
}

/******************************************************
*                 Yamaha set activated voices         *
******************************************************/
void YM_set_activeVoices(int v)
{
  voiceCut = smsk_table[v&7];
}
#endif

/******************************************************
*                  Yamaha get buffer                  *
******************************************************/
int * YM_get_buffer(void)
{
  return mixbuf + filter_cnt;
}

