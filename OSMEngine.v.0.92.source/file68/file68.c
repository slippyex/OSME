/*
 *                  file68 - "sc68" file functions
 *             Copyright (C) 1998-2007 Benjamin Gerard
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License as
 *  published by the Free Software Foundation; either version 2 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 *  02111-1307 USA
 *
 */

#include "config68.h"
#include "file68.h"
#include "alloc68.h"
#include "string68.h"
#include "istream68_mem.h"
#include "ice68.h"

#ifndef u64
# ifdef HAVE_STDINT_H
#  include <stdint.h>
#  define u64 uint_least64_t
# elif defined(_MSC_VER)
#  define u64 unsigned __int64
# elif defined(__GNUC__)
#  define u64 unsigned long long
# endif
#endif

#ifndef u64
# error "u64 must be defined as an integer of at least 64 bit"
#endif

#include <string.h>
#include <ctype.h>
#include <stdio.h>

#define FOURCC(A,B,C,D) ((int)( ((A)<<24) | ((B)<<16) | ((C)<<8) | (D) ))
#define ice_cc  FOURCC('i','c','e','!')
#define sndh_cc FOURCC('S','N','D','H')

static int LPeekBE(const void *a)
{
  int r;
  unsigned char *c = (unsigned char *) a;
  r = ((int)(signed char)c[0] << 24) + (c[1] << 16) + (c[2] << 8) + c[3];
  return r;
}

static int myatoi(const char *s, int i, int max, int * pv)
{
  int v = 0;
  for (; i<max; ++i) {
    int c = s[i] & 255;
    if (c>='0' && c<='9') {
      v = v * 10 + c - '0';
    } else {
      break;
    }
  }
  if (pv) *pv = v;
  return i;
}

static int sndh_is_magic(const char *buffer, int max)
{
  const int start = 6;
  int i=0, v = 0;
  if (max >= start) {
    for (i=start, v = LPeekBE(buffer); i < max && v != sndh_cc;
	 v = ((v<<8)| (buffer[i++]&255)) & 0xFFFFFFFF)
      ;
  }
  i = (v == sndh_cc) ? i-4: 0;
  return i;
}

/* Verify header , return # byte to alloc & read
 * or -1 if error
 * or -gzip_cc if may be gzipped
 * or -ice_cc if may be iced
 * or -sndh_cc if may be sndh
 * or 
 */
static int read_header(istream68_t * const is)
{
	char id[256];
	int l = 32;
	const int sndh_req = (l<=32) ? 32 : l;
	int l2;

	// /* Read ID v2 string */
	l2 = istream68_read(is, id, l);
	if(ice68_is_magic(id)) {
		return -ice_cc;
	} else {
		/* Need some more bytes for sndh */
		if (istream68_read(is, id+l, sndh_req-l) == sndh_req-l && sndh_is_magic(id,sndh_req)) {
			/* Must be done after gzip or ice becoz id-string may appear in
			* compressed buffer too.
			*/
			return -sndh_cc;
		}
    }
	return -1;

}

static char noname[] = SC68_NOFILENAME;


/* FR  = SEC * HZ
 * FR  = MS*HZ/1000
 *
 * SEC = FR / HZ
 * MS  = FR*1000/HZ
 */

static unsigned int frames_to_ms(unsigned int frames, unsigned int hz)
{
  u64 ms;

  ms = frames;
  ms *= 1000u;
  ms /= hz;

  return (unsigned int) ms;
}

static unsigned int ms_to_frames(unsigned int ms, unsigned int hz)
{
  u64 fr;

  fr =  ms;
  fr *= hz;
  fr /= 1000u;

  return (unsigned int ) fr;
}

/* This function inits all pointers for this music files It setup non
 * initialized data to defaut value.
 */
int my_valid(disk68_t * mb)
{
  music68_t *m;
  int i, previousdatasz = 0;
  void *previousdata = 0;
  char *author = noname;
  char *composer = 0;
  char *mname;
  char *converter = noname;
  char *ripper = noname;

  if (mb->nb_six <= 0) {
	return -1;
  }

  /* Ensure default music in valid range */
  if (mb->default_six < 0 || mb->default_six >= mb->nb_six) {
    mb->default_six = 0;
  }

  /* No name : set default */
  if (mb->name == 0) {
    mb->name = noname;
  }
  mname = mb->name;

  /* Disk total time : 00:00 */
  mb->time_ms = 0;

  /* Clear flags */
  mb->hwflags.all = 0;

  /* Init all music in this file */
  for (m = mb->mus, i = 0; m < mb->mus + mb->nb_six; m++, i++) {
    /* default load address */
    if (m->a0 == 0) {
      m->a0 = SC68_LOADADDR;
    }
    /* default replay frequency is 50Hz */
    if (m->frq == 0) {
      m->frq = 50;
    }

    /* Compute ms from frames prior to frames from ms. */ 
    if (m->frames) {
      m->time_ms = frames_to_ms(m->frames, m->frq);
    } else {
      m->frames = ms_to_frames(m->time_ms,m->frq);
    }

    /* Set start time in the disk. */
    m->start_ms = mb->time_ms;

    /* Advance disk total time. */
    mb->time_ms += m->time_ms;

    /* default mode is YM2149 (Atari ST) */
    if (m->hwflags.all == 0) {
      m->hwflags.bit.ym = 1;
    }
    mb->hwflags.all |= m->hwflags.all;

    /* default music name is file name */
    mname = m->name = (m->name == 0) ? mname : m->name;
    /* default author */
    author = m->author = (m->author == 0) ? author : m->author;
    /* default composer is author */
    composer = m->composer = (m->composer == 0) ?
	((composer == 0) ? m->author : composer) : m->composer;
    /* default converter is the empty string */
    converter = m->converter = (m->converter == 0) ?
        ((converter == 0) ? m->converter : converter) : m->converter;
    /* default copier is the empty string */
    ripper = m->ripper = (m->ripper == 0) ?
        ((ripper == 0) ? m->ripper : ripper) : m->ripper;
    /* use data from previuous music */
    if (m->data == 0) {
      m->data = (char *) previousdata;
      m->datasz = previousdatasz;
    }
    if (m->data == 0) {
		return -1;
    }
    previousdata = m->data;
    previousdatasz = m->datasz;
  }

  return 0;
}

disk68_t * file68_load_mem(const void * buffer, int len)
{
  disk68_t * d;
  istream68_t * is;

  is = istream68_mem_create((void *)buffer,len,1);
  d = istream68_open(is) ? 0 : file68_load(is);
  istream68_destroy(is);

  return d;
}

static int sndh_info(disk68_t * mb, int len)
{
  int frq = 0, time = 0 , musicmon = 0;
  int i;
  int unknowns = 0;
  const int unknowns_max = 8;
  int fail = 0;
  char * b = mb->data;
  char empty_tag[4] = { 0, 0, 0, 0 };

  /* Default */
  mb->mus[0].data = b;
  mb->mus[0].datasz = len;
  mb->nb_six = 0; /* Make validate failed */
  mb->mus[0].replay = "sndh_ice";

  i = sndh_is_magic(mb->data, len);
  if (!i) {
    /* should not happen since we already have tested it. */
    return -1;
  }

  i += 4; /* Skip sndh_cc */
  len -= 4;

  /* $$$ Hacky:
     Some music have 0 after values. I don't know what are
     sndh rules. May be 0 must be skipped or may be tag must be word
     aligned.
     Anyway the current parser allows a given number of successive
     unknown tags. May be this number should be increase in order to prevent
     some "large" unknown tag to break the parser.
  */

  while (i < len) {
    char * s;
    int unknown;

    s = 0;
    unknown = 0;
    if (!memcmp(b+i,"COMM",4)) {
      /* Composer */
      s = mb->mus[0].author = b+i+4;
    } else if (!memcmp(b+i,"TITL",4)) { /* title    */
      /* Title */
      s = mb->name = b+i+4;
    } else if (!memcmp(b+i,"RIPP",4)) {
      /* Ripper    */
      s = mb->mus[0].ripper = b+i+4;
    } else if (!memcmp(b+i,"CONV",4)) {
      /* Converter */
      s = mb->mus[0].converter = b+i+4;
    } else if (!memcmp(b+i,"MuMo",4)) {
      /* Music Mon ???  */
      //debugwrapper(-1,"FOUND MuMo (don't know what to do ith that)\n");
      musicmon = 1;
      i += 4;
    } else if (!memcmp(b+i,"TIME",4)) {
      /* Time in second */
      time = (((unsigned char)*(b + i + 4)) << 8) |
             ((unsigned char)*(b + i + 5));
      i += 6;
    } else if (!memcmp(b+i,"##",2)) {
      /* +'xx' number of track  */
      i = myatoi(b, i+2, len, &mb->nb_six);
      while( i < len && *(b + i) == 0 ) {
        i++;
      }
    } else if (!memcmp(b+i,"!V",2)) {
      /* +string VBL frq */
      if (!frq) {
	i = myatoi(b, i+2, len, &frq);
      }
    } else if (!memcmp(b+i,"**",2)) {
      /* FX +string 2 char ??? */
      i += 4;
    }
    else if (!memcmp(b+i, "YEAR", 4)) {
      /* year */
      s = b+i+4;
    }
    else if( *(b+i) == 'T' && (*(b+i+1) == 'A' ||
                               *(b+i+1) == 'B' ||
                               *(b+i+1) == 'C' ||
                               *(b+i+1) == 'D') ) {
      i = myatoi(b, i+2, len, &frq);
      while( i < len && *(b + i) == 0 ) {
        i++;
      }
    }
    else if( memcmp( b + i, empty_tag, 4 ) == 0 ||
             memcmp( b + i, "HDNS", 4 ) == 0 ) {
      i = len;
    } else { 
      /* skip until next 0 byte, as long as it's inside the tag area */

      i += 4;
      while( *(b + i) != 0 && i < len ) {
        i++;
      }

      unknown = 1;
    }

    if (unknown) {
      ++unknowns;
         /* Unkwown tag, finish here. */
      ++i;
      if (fail || unknowns >= unknowns_max) {
	i = len;
      }
      unknown = 0;
    } else {
      unknowns = 0; /* Reset successive unkwown. */
      if (s) {
	int j,k,c;
	for (j=k=0; c=(s[j]&255), c; ++j) {
	  if (c <= 32) s[j] = 32;
	  else k=j+1;
	}
	s[k] = 0; /* Strip trailing space */
	i += j + 5;

        /* skip the trailing null chars */
        while( i < len && *(b + i) == 0 ) {
          i++;
        }
      }
    }

  }
  if (mb->nb_six > SC68_MAX_TRACK) {
    mb->nb_six = SC68_MAX_TRACK;
  }
  time *= 1000;
  for (i=0; i<mb->nb_six; ++i) {
    mb->mus[i].d0 = i+1;
    mb->mus[i].loop = 1;
    mb->mus[i].frq = frq;
    mb->mus[i].time_ms = time;
  }
  return 0;
}

/* Load , allocate memory and valid struct for SC68 music
 */
disk68_t * file68_load(istream68_t * is) {
	disk68_t *mb = 0;
	int len, room;
	int chk_size;
	int opened = 0;
	music68_t *cursix;
	char *b;
	const char *fname = istream68_filename(is);

	/* Read header and get data length. */
	if (len = read_header(is), len < 0) {
		/* Verify tells it is a gzip or unice file, so we may give it a try.
		 */
		if (1) {
			void * buffer = 0;
			int l;
			switch (len) {
				case -ice_cc:
					if (istream68_seek_to(is,0) == 0) {
						buffer = ice68_load(is, &l);
					}
					break;
				case -sndh_cc:
					if (istream68_seek_to(is,0) != 0) {
						break;
					}
					len = istream68_length(is);
					if (len <= 32) {
						break;
					}
					mb = (disk68_t*)alloc68(sizeof(*mb) + len);
					if (!mb) {
						break;
					}
					memset(mb,0,sizeof(*mb));
					if (istream68_read(is, mb->data, len) != len) {
						break;
					}
					if (sndh_info(mb, len)) {
						break;
					}
					goto validate;
				}
				if (buffer) {
					mb = file68_load_mem(buffer, l);
					free68(buffer);
					if (mb) {
						return mb;
					}
				}
		    }
		    goto error;
		}
		room = len + sizeof(disk68_t) - sizeof(mb->data);
		mb = (disk68_t*)alloc68(room);
		if (!mb) {
			goto error;
		}
		memset(mb, 0, room);

		if (istream68_read(is, mb->data, len) != len) {
			goto error;
		}

		/* Check it */
		if (len) {
			goto error;
		}

validate:
	if (my_valid(mb)) {
		goto error;
	}

 already_valid:
	if (opened) {
		istream68_close(is);
	}
	return mb;

error:
	if (opened) {
		istream68_close(is);
	}
	free68(mb);
	return 0;
}
