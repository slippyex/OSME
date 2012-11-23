#include "emu68/emu68.h"

static void BTST_reg(int b, int reg0)
{
  u32 a = reg68.d[reg0];
  b &= 31;
  BTST(a,b);
  ADDCYCLE(2);
}

static void BTST_mem(int b, int mode, int reg0)
{
  u32 addr = get_eab[mode](reg0);
  u32 a = read_B(addr);
  b &= 7;
  BTST(a,b);
  ADDCYCLE(0);
}

static void BCHG_reg(int b, int reg0)
{
  u32 a = reg68.d[reg0];
  b &= 31;
  BCHG(a,b);
  reg68.d[reg0] = a;
  ADDCYCLE(4);
}

static void BCHG_mem(int b, int mode, int reg0)
{
  u32 addr = get_eab[mode](reg0);
  u32 a = read_B(addr);
  b &= 7;
  BCHG(a,b);
  write_B(addr,a);
  ADDCYCLE(4);
}

static void BCLR_reg(int b, int reg0)
{
  u32 a = reg68.d[reg0];
  b &= 31;
  BCLR(a,b);
  reg68.d[reg0] = a;
  ADDCYCLE(6);
}

static void BCLR_mem(int b, int mode, int reg0)
{
  u32 addr = get_eab[mode](reg0);
  u32 a = read_B(addr);
  b &= 7;
  BCLR(a,b);
  write_B(addr,a);
  ADDCYCLE(4);
}

static void BSET_reg(int b, int reg0)
{
  u32 a = reg68.d[reg0];
  b &= 31;
  BSET(a,b);
  reg68.d[reg0] = a;
  ADDCYCLE(4);
}

static void BSET_mem(int b, int mode, int reg0)
{
  u32 addr = get_eab[mode](reg0);
  u32 a = read_B(addr);
  b &= 7;
  BSET(a,b);
  write_B(addr,a);
  ADDCYCLE(4);
}

static void l0_ill(u32 reg0)
{
  reg0=reg0; ILLEGAL;
}

static void l0_ORb0(u32 reg0)
{
  /* OR.B #imm,Dy */
  s32 a,b,s;
  a = get_nextw()<<24;
  b = reg68.d[reg0]<<24;
  ORB(s,a,b);
  reg68.d[reg0] = (reg68.d[reg0]&0xffffff00) + ((u32)s>>24);
}

static void l0_ANDb0(u32 reg0)
{
  /* AND.B #imm,Dy */
  s32 a,b,s;
  a = get_nextw()<<24;
  b = reg68.d[reg0]<<24;
  ANDB(s,a,b);
  reg68.d[reg0] = (reg68.d[reg0]&0xffffff00) + ((u32)s>>24);
}

static void l0_EORb0(u32 reg0)
{
  /* EOR.B #imm,Dy */
  s32 a,b,s;
  a = get_nextw()<<24;
  b = reg68.d[reg0]<<24;
  EORB(s,a,b);
  reg68.d[reg0] = (reg68.d[reg0]&0xffffff00) + ((u32)s>>24);
}

static void l0_ADDb0(u32 reg0)
{
  /* ADD.B #imm,Dy */
  s32 a,b,s;
  a = get_nextw()<<24;
  b = reg68.d[reg0]<<24;
  ADDB(s,a,b);
  reg68.d[reg0] = (reg68.d[reg0]&0xffffff00) + ((u32)s>>24);
}

static void l0_SUBb0(u32 reg0)
{
  /* SUB.B #imm,Dy */
  s32 a,b,s;
  a = get_nextw()<<24;
  b = reg68.d[reg0]<<24;
  SUBB(s,a,b);
  reg68.d[reg0] = (reg68.d[reg0]&0xffffff00) + ((u32)s>>24);
}

static void l0_CMPb0(u32 reg0)
{
  /* CMP.B #imm,Dy */
  s32 a,b;
  a = get_nextw()<<24;
  b = reg68.d[reg0]<<24;
  CMPB(a,b);
}

static void l0_ORw0(u32 reg0)
{
  /* OR.W #imm,Dy */
  s32 a,b,s;
  a = get_nextw()<<16;
  b = reg68.d[reg0]<<16;
  ORW(s,a,b);
  reg68.d[reg0] = (reg68.d[reg0]&0xffff0000) + ((u32)s>>16);
}

static void l0_ANDw0(u32 reg0)
{
  /* AND.W #imm,Dy */
  s32 a,b,s;
  a = get_nextw()<<16;
  b = reg68.d[reg0]<<16;
  ANDW(s,a,b);
  reg68.d[reg0] = (reg68.d[reg0]&0xffff0000) + ((u32)s>>16);
}

static void l0_EORw0(u32 reg0)
{
  /* EOR.W #imm,Dy */
  s32 a,b,s;
  a = get_nextw()<<16;
  b = reg68.d[reg0]<<16;
  EORW(s,a,b);
  reg68.d[reg0] = (reg68.d[reg0]&0xffff0000) + ((u32)s>>16);
}

static void l0_ADDw0(u32 reg0)
{
  /* ADD.W #imm,Dy */
  s32 a,b,s;
  a = get_nextw()<<16;
  b = reg68.d[reg0]<<16;
  ADDW(s,a,b);
  reg68.d[reg0] = (reg68.d[reg0]&0xffff0000) + ((u32)s>>16);
}

static void l0_SUBw0(u32 reg0)
{
  /* SUB.W #imm,Dy */
  s32 a,b,s;
  a = get_nextw()<<16;
  b = reg68.d[reg0]<<16;
  SUBW(s,a,b);
  reg68.d[reg0] = (reg68.d[reg0]&0xffff0000) + ((u32)s>>16);
}

static void l0_CMPw0(u32 reg0)
{
  /* CMP.W #imm,Dy */
  s32 a,b;
  a = get_nextw()<<16;
  b = reg68.d[reg0]<<16;
  CMPW(a,b);
}

static void l0_ORl0(u32 reg0)
{
  /* OR.L #imm,Dy */
  s32 a,b,s;
  a = get_nextl()<<0;
  b = reg68.d[reg0]<<0;
  ORL(s,a,b);
  reg68.d[reg0] = (reg68.d[reg0]&0) + ((u32)s>>0);
}

static void l0_ANDl0(u32 reg0)
{
  /* AND.L #imm,Dy */
  s32 a,b,s;
  a = get_nextl()<<0;
  b = reg68.d[reg0]<<0;
  ANDL(s,a,b);
  reg68.d[reg0] = (reg68.d[reg0]&0) + ((u32)s>>0);
}

static void l0_EORl0(u32 reg0)
{
  /* EOR.L #imm,Dy */
  s32 a,b,s;
  a = get_nextl()<<0;
  b = reg68.d[reg0]<<0;
  EORL(s,a,b);
  reg68.d[reg0] = (reg68.d[reg0]&0) + ((u32)s>>0);
}

static void l0_ADDl0(u32 reg0)
{
  /* ADD.L #imm,Dy */
  s32 a,b,s;
  a = get_nextl()<<0;
  b = reg68.d[reg0]<<0;
  ADDL(s,a,b);
  reg68.d[reg0] = (reg68.d[reg0]&0) + ((u32)s>>0);
}

static void l0_SUBl0(u32 reg0)
{
  /* SUB.L #imm,Dy */
  s32 a,b,s;
  a = get_nextl()<<0;
  b = reg68.d[reg0]<<0;
  SUBL(s,a,b);
  reg68.d[reg0] = (reg68.d[reg0]&0) + ((u32)s>>0);
}

static void l0_CMPl0(u32 reg0)
{
  /* CMP.L #imm,Dy */
  s32 a,b;
  a = get_nextl()<<0;
  b = reg68.d[reg0]<<0;
  CMPL(a,b);
}

static void l0_ORb2(u32 reg0)
{
  /* OR.B #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<24;
  addr = get_eab[2](reg0);
  b = read_B(addr)<<24;
  ORB(s,a,b);
  write_B(addr,(u32)s>>24);
}

static void l0_ANDb2(u32 reg0)
{
  /* AND.B #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<24;
  addr = get_eab[2](reg0);
  b = read_B(addr)<<24;
  ANDB(s,a,b);
  write_B(addr,(u32)s>>24);
}

static void l0_EORb2(u32 reg0)
{
  /* EOR.B #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<24;
  addr = get_eab[2](reg0);
  b = read_B(addr)<<24;
  EORB(s,a,b);
  write_B(addr,(u32)s>>24);
}

static void l0_ADDb2(u32 reg0)
{
  /* ADD.B #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<24;
  addr = get_eab[2](reg0);
  b = read_B(addr)<<24;
  ADDB(s,a,b);
  write_B(addr,(u32)s>>24);
}

static void l0_SUBb2(u32 reg0)
{
  /* SUB.B #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<24;
  addr = get_eab[2](reg0);
  b = read_B(addr)<<24;
  SUBB(s,a,b);
  write_B(addr,(u32)s>>24);
}

static void l0_CMPb2(u32 reg0)
{
  /* CMP.B #imm,<Ae> */
  s32 a,b;
  u32 addr;
  a = get_nextw()<<24;
  addr = get_eab[2](reg0);
  b = read_B(addr)<<24;
  CMPB(a,b);
}

static void l0_ORw2(u32 reg0)
{
  /* OR.W #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<16;
  addr = get_eaw[2](reg0);
  b = read_W(addr)<<16;
  ORW(s,a,b);
  write_W(addr,(u32)s>>16);
}

static void l0_ANDw2(u32 reg0)
{
  /* AND.W #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<16;
  addr = get_eaw[2](reg0);
  b = read_W(addr)<<16;
  ANDW(s,a,b);
  write_W(addr,(u32)s>>16);
}

static void l0_EORw2(u32 reg0)
{
  /* EOR.W #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<16;
  addr = get_eaw[2](reg0);
  b = read_W(addr)<<16;
  EORW(s,a,b);
  write_W(addr,(u32)s>>16);
}

static void l0_ADDw2(u32 reg0)
{
  /* ADD.W #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<16;
  addr = get_eaw[2](reg0);
  b = read_W(addr)<<16;
  ADDW(s,a,b);
  write_W(addr,(u32)s>>16);
}

static void l0_SUBw2(u32 reg0)
{
  /* SUB.W #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<16;
  addr = get_eaw[2](reg0);
  b = read_W(addr)<<16;
  SUBW(s,a,b);
  write_W(addr,(u32)s>>16);
}

static void l0_CMPw2(u32 reg0)
{
  /* CMP.W #imm,<Ae> */
  s32 a,b;
  u32 addr;
  a = get_nextw()<<16;
  addr = get_eaw[2](reg0);
  b = read_W(addr)<<16;
  CMPW(a,b);
}

static void l0_ORl2(u32 reg0)
{
  /* OR.L #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextl()<<0;
  addr = get_eal[2](reg0);
  b = read_L(addr)<<0;
  ORL(s,a,b);
  write_L(addr,(u32)s>>0);
}

static void l0_ANDl2(u32 reg0)
{
  /* AND.L #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextl()<<0;
  addr = get_eal[2](reg0);
  b = read_L(addr)<<0;
  ANDL(s,a,b);
  write_L(addr,(u32)s>>0);
}

static void l0_EORl2(u32 reg0)
{
  /* EOR.L #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextl()<<0;
  addr = get_eal[2](reg0);
  b = read_L(addr)<<0;
  EORL(s,a,b);
  write_L(addr,(u32)s>>0);
}

static void l0_ADDl2(u32 reg0)
{
  /* ADD.L #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextl()<<0;
  addr = get_eal[2](reg0);
  b = read_L(addr)<<0;
  ADDL(s,a,b);
  write_L(addr,(u32)s>>0);
}

static void l0_SUBl2(u32 reg0)
{
  /* SUB.L #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextl()<<0;
  addr = get_eal[2](reg0);
  b = read_L(addr)<<0;
  SUBL(s,a,b);
  write_L(addr,(u32)s>>0);
}

static void l0_CMPl2(u32 reg0)
{
  /* CMP.L #imm,<Ae> */
  s32 a,b;
  u32 addr;
  a = get_nextl()<<0;
  addr = get_eal[2](reg0);
  b = read_L(addr)<<0;
  CMPL(a,b);
}

static void l0_ORb3(u32 reg0)
{
  /* OR.B #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<24;
  addr = get_eab[3](reg0);
  b = read_B(addr)<<24;
  ORB(s,a,b);
  write_B(addr,(u32)s>>24);
}

static void l0_ANDb3(u32 reg0)
{
  /* AND.B #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<24;
  addr = get_eab[3](reg0);
  b = read_B(addr)<<24;
  ANDB(s,a,b);
  write_B(addr,(u32)s>>24);
}

static void l0_EORb3(u32 reg0)
{
  /* EOR.B #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<24;
  addr = get_eab[3](reg0);
  b = read_B(addr)<<24;
  EORB(s,a,b);
  write_B(addr,(u32)s>>24);
}

static void l0_ADDb3(u32 reg0)
{
  /* ADD.B #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<24;
  addr = get_eab[3](reg0);
  b = read_B(addr)<<24;
  ADDB(s,a,b);
  write_B(addr,(u32)s>>24);
}

static void l0_SUBb3(u32 reg0)
{
  /* SUB.B #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<24;
  addr = get_eab[3](reg0);
  b = read_B(addr)<<24;
  SUBB(s,a,b);
  write_B(addr,(u32)s>>24);
}

static void l0_CMPb3(u32 reg0)
{
  /* CMP.B #imm,<Ae> */
  s32 a,b;
  u32 addr;
  a = get_nextw()<<24;
  addr = get_eab[3](reg0);
  b = read_B(addr)<<24;
  CMPB(a,b);
}

static void l0_ORw3(u32 reg0)
{
  /* OR.W #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<16;
  addr = get_eaw[3](reg0);
  b = read_W(addr)<<16;
  ORW(s,a,b);
  write_W(addr,(u32)s>>16);
}

static void l0_ANDw3(u32 reg0)
{
  /* AND.W #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<16;
  addr = get_eaw[3](reg0);
  b = read_W(addr)<<16;
  ANDW(s,a,b);
  write_W(addr,(u32)s>>16);
}

static void l0_EORw3(u32 reg0)
{
  /* EOR.W #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<16;
  addr = get_eaw[3](reg0);
  b = read_W(addr)<<16;
  EORW(s,a,b);
  write_W(addr,(u32)s>>16);
}

static void l0_ADDw3(u32 reg0)
{
  /* ADD.W #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<16;
  addr = get_eaw[3](reg0);
  b = read_W(addr)<<16;
  ADDW(s,a,b);
  write_W(addr,(u32)s>>16);
}

static void l0_SUBw3(u32 reg0)
{
  /* SUB.W #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<16;
  addr = get_eaw[3](reg0);
  b = read_W(addr)<<16;
  SUBW(s,a,b);
  write_W(addr,(u32)s>>16);
}

static void l0_CMPw3(u32 reg0)
{
  /* CMP.W #imm,<Ae> */
  s32 a,b;
  u32 addr;
  a = get_nextw()<<16;
  addr = get_eaw[3](reg0);
  b = read_W(addr)<<16;
  CMPW(a,b);
}

static void l0_ORl3(u32 reg0)
{
  /* OR.L #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextl()<<0;
  addr = get_eal[3](reg0);
  b = read_L(addr)<<0;
  ORL(s,a,b);
  write_L(addr,(u32)s>>0);
}

static void l0_ANDl3(u32 reg0)
{
  /* AND.L #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextl()<<0;
  addr = get_eal[3](reg0);
  b = read_L(addr)<<0;
  ANDL(s,a,b);
  write_L(addr,(u32)s>>0);
}

static void l0_EORl3(u32 reg0)
{
  /* EOR.L #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextl()<<0;
  addr = get_eal[3](reg0);
  b = read_L(addr)<<0;
  EORL(s,a,b);
  write_L(addr,(u32)s>>0);
}

static void l0_ADDl3(u32 reg0)
{
  /* ADD.L #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextl()<<0;
  addr = get_eal[3](reg0);
  b = read_L(addr)<<0;
  ADDL(s,a,b);
  write_L(addr,(u32)s>>0);
}

static void l0_SUBl3(u32 reg0)
{
  /* SUB.L #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextl()<<0;
  addr = get_eal[3](reg0);
  b = read_L(addr)<<0;
  SUBL(s,a,b);
  write_L(addr,(u32)s>>0);
}

static void l0_CMPl3(u32 reg0)
{
  /* CMP.L #imm,<Ae> */
  s32 a,b;
  u32 addr;
  a = get_nextl()<<0;
  addr = get_eal[3](reg0);
  b = read_L(addr)<<0;
  CMPL(a,b);
}

static void l0_ORb4(u32 reg0)
{
  /* OR.B #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<24;
  addr = get_eab[4](reg0);
  b = read_B(addr)<<24;
  ORB(s,a,b);
  write_B(addr,(u32)s>>24);
}

static void l0_ANDb4(u32 reg0)
{
  /* AND.B #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<24;
  addr = get_eab[4](reg0);
  b = read_B(addr)<<24;
  ANDB(s,a,b);
  write_B(addr,(u32)s>>24);
}

static void l0_EORb4(u32 reg0)
{
  /* EOR.B #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<24;
  addr = get_eab[4](reg0);
  b = read_B(addr)<<24;
  EORB(s,a,b);
  write_B(addr,(u32)s>>24);
}

static void l0_ADDb4(u32 reg0)
{
  /* ADD.B #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<24;
  addr = get_eab[4](reg0);
  b = read_B(addr)<<24;
  ADDB(s,a,b);
  write_B(addr,(u32)s>>24);
}

static void l0_SUBb4(u32 reg0)
{
  /* SUB.B #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<24;
  addr = get_eab[4](reg0);
  b = read_B(addr)<<24;
  SUBB(s,a,b);
  write_B(addr,(u32)s>>24);
}

static void l0_CMPb4(u32 reg0)
{
  /* CMP.B #imm,<Ae> */
  s32 a,b;
  u32 addr;
  a = get_nextw()<<24;
  addr = get_eab[4](reg0);
  b = read_B(addr)<<24;
  CMPB(a,b);
}

static void l0_ORw4(u32 reg0)
{
  /* OR.W #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<16;
  addr = get_eaw[4](reg0);
  b = read_W(addr)<<16;
  ORW(s,a,b);
  write_W(addr,(u32)s>>16);
}

static void l0_ANDw4(u32 reg0)
{
  /* AND.W #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<16;
  addr = get_eaw[4](reg0);
  b = read_W(addr)<<16;
  ANDW(s,a,b);
  write_W(addr,(u32)s>>16);
}

static void l0_EORw4(u32 reg0)
{
  /* EOR.W #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<16;
  addr = get_eaw[4](reg0);
  b = read_W(addr)<<16;
  EORW(s,a,b);
  write_W(addr,(u32)s>>16);
}

static void l0_ADDw4(u32 reg0)
{
  /* ADD.W #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<16;
  addr = get_eaw[4](reg0);
  b = read_W(addr)<<16;
  ADDW(s,a,b);
  write_W(addr,(u32)s>>16);
}

static void l0_SUBw4(u32 reg0)
{
  /* SUB.W #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<16;
  addr = get_eaw[4](reg0);
  b = read_W(addr)<<16;
  SUBW(s,a,b);
  write_W(addr,(u32)s>>16);
}

static void l0_CMPw4(u32 reg0)
{
  /* CMP.W #imm,<Ae> */
  s32 a,b;
  u32 addr;
  a = get_nextw()<<16;
  addr = get_eaw[4](reg0);
  b = read_W(addr)<<16;
  CMPW(a,b);
}

static void l0_ORl4(u32 reg0)
{
  /* OR.L #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextl()<<0;
  addr = get_eal[4](reg0);
  b = read_L(addr)<<0;
  ORL(s,a,b);
  write_L(addr,(u32)s>>0);
}

static void l0_ANDl4(u32 reg0)
{
  /* AND.L #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextl()<<0;
  addr = get_eal[4](reg0);
  b = read_L(addr)<<0;
  ANDL(s,a,b);
  write_L(addr,(u32)s>>0);
}

static void l0_EORl4(u32 reg0)
{
  /* EOR.L #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextl()<<0;
  addr = get_eal[4](reg0);
  b = read_L(addr)<<0;
  EORL(s,a,b);
  write_L(addr,(u32)s>>0);
}

static void l0_ADDl4(u32 reg0)
{
  /* ADD.L #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextl()<<0;
  addr = get_eal[4](reg0);
  b = read_L(addr)<<0;
  ADDL(s,a,b);
  write_L(addr,(u32)s>>0);
}

static void l0_SUBl4(u32 reg0)
{
  /* SUB.L #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextl()<<0;
  addr = get_eal[4](reg0);
  b = read_L(addr)<<0;
  SUBL(s,a,b);
  write_L(addr,(u32)s>>0);
}

static void l0_CMPl4(u32 reg0)
{
  /* CMP.L #imm,<Ae> */
  s32 a,b;
  u32 addr;
  a = get_nextl()<<0;
  addr = get_eal[4](reg0);
  b = read_L(addr)<<0;
  CMPL(a,b);
}

static void l0_ORb5(u32 reg0)
{
  /* OR.B #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<24;
  addr = get_eab[5](reg0);
  b = read_B(addr)<<24;
  ORB(s,a,b);
  write_B(addr,(u32)s>>24);
}

static void l0_ANDb5(u32 reg0)
{
  /* AND.B #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<24;
  addr = get_eab[5](reg0);
  b = read_B(addr)<<24;
  ANDB(s,a,b);
  write_B(addr,(u32)s>>24);
}

static void l0_EORb5(u32 reg0)
{
  /* EOR.B #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<24;
  addr = get_eab[5](reg0);
  b = read_B(addr)<<24;
  EORB(s,a,b);
  write_B(addr,(u32)s>>24);
}

static void l0_ADDb5(u32 reg0)
{
  /* ADD.B #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<24;
  addr = get_eab[5](reg0);
  b = read_B(addr)<<24;
  ADDB(s,a,b);
  write_B(addr,(u32)s>>24);
}

static void l0_SUBb5(u32 reg0)
{
  /* SUB.B #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<24;
  addr = get_eab[5](reg0);
  b = read_B(addr)<<24;
  SUBB(s,a,b);
  write_B(addr,(u32)s>>24);
}

static void l0_CMPb5(u32 reg0)
{
  /* CMP.B #imm,<Ae> */
  s32 a,b;
  u32 addr;
  a = get_nextw()<<24;
  addr = get_eab[5](reg0);
  b = read_B(addr)<<24;
  CMPB(a,b);
}

static void l0_ORw5(u32 reg0)
{
  /* OR.W #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<16;
  addr = get_eaw[5](reg0);
  b = read_W(addr)<<16;
  ORW(s,a,b);
  write_W(addr,(u32)s>>16);
}

static void l0_ANDw5(u32 reg0)
{
  /* AND.W #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<16;
  addr = get_eaw[5](reg0);
  b = read_W(addr)<<16;
  ANDW(s,a,b);
  write_W(addr,(u32)s>>16);
}

static void l0_EORw5(u32 reg0)
{
  /* EOR.W #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<16;
  addr = get_eaw[5](reg0);
  b = read_W(addr)<<16;
  EORW(s,a,b);
  write_W(addr,(u32)s>>16);
}

static void l0_ADDw5(u32 reg0)
{
  /* ADD.W #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<16;
  addr = get_eaw[5](reg0);
  b = read_W(addr)<<16;
  ADDW(s,a,b);
  write_W(addr,(u32)s>>16);
}

static void l0_SUBw5(u32 reg0)
{
  /* SUB.W #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<16;
  addr = get_eaw[5](reg0);
  b = read_W(addr)<<16;
  SUBW(s,a,b);
  write_W(addr,(u32)s>>16);
}

static void l0_CMPw5(u32 reg0)
{
  /* CMP.W #imm,<Ae> */
  s32 a,b;
  u32 addr;
  a = get_nextw()<<16;
  addr = get_eaw[5](reg0);
  b = read_W(addr)<<16;
  CMPW(a,b);
}

static void l0_ORl5(u32 reg0)
{
  /* OR.L #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextl()<<0;
  addr = get_eal[5](reg0);
  b = read_L(addr)<<0;
  ORL(s,a,b);
  write_L(addr,(u32)s>>0);
}

static void l0_ANDl5(u32 reg0)
{
  /* AND.L #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextl()<<0;
  addr = get_eal[5](reg0);
  b = read_L(addr)<<0;
  ANDL(s,a,b);
  write_L(addr,(u32)s>>0);
}

static void l0_EORl5(u32 reg0)
{
  /* EOR.L #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextl()<<0;
  addr = get_eal[5](reg0);
  b = read_L(addr)<<0;
  EORL(s,a,b);
  write_L(addr,(u32)s>>0);
}

static void l0_ADDl5(u32 reg0)
{
  /* ADD.L #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextl()<<0;
  addr = get_eal[5](reg0);
  b = read_L(addr)<<0;
  ADDL(s,a,b);
  write_L(addr,(u32)s>>0);
}

static void l0_SUBl5(u32 reg0)
{
  /* SUB.L #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextl()<<0;
  addr = get_eal[5](reg0);
  b = read_L(addr)<<0;
  SUBL(s,a,b);
  write_L(addr,(u32)s>>0);
}

static void l0_CMPl5(u32 reg0)
{
  /* CMP.L #imm,<Ae> */
  s32 a,b;
  u32 addr;
  a = get_nextl()<<0;
  addr = get_eal[5](reg0);
  b = read_L(addr)<<0;
  CMPL(a,b);
}

static void l0_ORb6(u32 reg0)
{
  /* OR.B #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<24;
  addr = get_eab[6](reg0);
  b = read_B(addr)<<24;
  ORB(s,a,b);
  write_B(addr,(u32)s>>24);
}

static void l0_ANDb6(u32 reg0)
{
  /* AND.B #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<24;
  addr = get_eab[6](reg0);
  b = read_B(addr)<<24;
  ANDB(s,a,b);
  write_B(addr,(u32)s>>24);
}

static void l0_EORb6(u32 reg0)
{
  /* EOR.B #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<24;
  addr = get_eab[6](reg0);
  b = read_B(addr)<<24;
  EORB(s,a,b);
  write_B(addr,(u32)s>>24);
}

static void l0_ADDb6(u32 reg0)
{
  /* ADD.B #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<24;
  addr = get_eab[6](reg0);
  b = read_B(addr)<<24;
  ADDB(s,a,b);
  write_B(addr,(u32)s>>24);
}

static void l0_SUBb6(u32 reg0)
{
  /* SUB.B #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<24;
  addr = get_eab[6](reg0);
  b = read_B(addr)<<24;
  SUBB(s,a,b);
  write_B(addr,(u32)s>>24);
}

static void l0_CMPb6(u32 reg0)
{
  /* CMP.B #imm,<Ae> */
  s32 a,b;
  u32 addr;
  a = get_nextw()<<24;
  addr = get_eab[6](reg0);
  b = read_B(addr)<<24;
  CMPB(a,b);
}

static void l0_ORw6(u32 reg0)
{
  /* OR.W #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<16;
  addr = get_eaw[6](reg0);
  b = read_W(addr)<<16;
  ORW(s,a,b);
  write_W(addr,(u32)s>>16);
}

static void l0_ANDw6(u32 reg0)
{
  /* AND.W #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<16;
  addr = get_eaw[6](reg0);
  b = read_W(addr)<<16;
  ANDW(s,a,b);
  write_W(addr,(u32)s>>16);
}

static void l0_EORw6(u32 reg0)
{
  /* EOR.W #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<16;
  addr = get_eaw[6](reg0);
  b = read_W(addr)<<16;
  EORW(s,a,b);
  write_W(addr,(u32)s>>16);
}

static void l0_ADDw6(u32 reg0)
{
  /* ADD.W #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<16;
  addr = get_eaw[6](reg0);
  b = read_W(addr)<<16;
  ADDW(s,a,b);
  write_W(addr,(u32)s>>16);
}

static void l0_SUBw6(u32 reg0)
{
  /* SUB.W #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<16;
  addr = get_eaw[6](reg0);
  b = read_W(addr)<<16;
  SUBW(s,a,b);
  write_W(addr,(u32)s>>16);
}

static void l0_CMPw6(u32 reg0)
{
  /* CMP.W #imm,<Ae> */
  s32 a,b;
  u32 addr;
  a = get_nextw()<<16;
  addr = get_eaw[6](reg0);
  b = read_W(addr)<<16;
  CMPW(a,b);
}

static void l0_ORl6(u32 reg0)
{
  /* OR.L #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextl()<<0;
  addr = get_eal[6](reg0);
  b = read_L(addr)<<0;
  ORL(s,a,b);
  write_L(addr,(u32)s>>0);
}

static void l0_ANDl6(u32 reg0)
{
  /* AND.L #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextl()<<0;
  addr = get_eal[6](reg0);
  b = read_L(addr)<<0;
  ANDL(s,a,b);
  write_L(addr,(u32)s>>0);
}

static void l0_EORl6(u32 reg0)
{
  /* EOR.L #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextl()<<0;
  addr = get_eal[6](reg0);
  b = read_L(addr)<<0;
  EORL(s,a,b);
  write_L(addr,(u32)s>>0);
}

static void l0_ADDl6(u32 reg0)
{
  /* ADD.L #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextl()<<0;
  addr = get_eal[6](reg0);
  b = read_L(addr)<<0;
  ADDL(s,a,b);
  write_L(addr,(u32)s>>0);
}

static void l0_SUBl6(u32 reg0)
{
  /* SUB.L #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextl()<<0;
  addr = get_eal[6](reg0);
  b = read_L(addr)<<0;
  SUBL(s,a,b);
  write_L(addr,(u32)s>>0);
}

static void l0_CMPl6(u32 reg0)
{
  /* CMP.L #imm,<Ae> */
  s32 a,b;
  u32 addr;
  a = get_nextl()<<0;
  addr = get_eal[6](reg0);
  b = read_L(addr)<<0;
  CMPL(a,b);
}

static void l0_ORb7(u32 reg0)
{
  if(reg0==4)
  {
    u32 a;
    a = get_nextw()&255;
    reg68.sr |= a;
  }
  else
  {
  /* OR.B #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<24;
  addr = get_eab[7](reg0);
  b = read_B(addr)<<24;
  ORB(s,a,b);
  write_B(addr,(u32)s>>24);
  }
}

static void l0_ANDb7(u32 reg0)
{
  if(reg0==4)
  {
    u32 a;
    a = get_nextw()|0xFF00;
    reg68.sr &= a;
  }
  else
  {
  /* AND.B #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<24;
  addr = get_eab[7](reg0);
  b = read_B(addr)<<24;
  ANDB(s,a,b);
  write_B(addr,(u32)s>>24);
  }
}

static void l0_EORb7(u32 reg0)
{
  if(reg0==4)
  {
    u32 a;
    a = get_nextw()&255;
    reg68.sr ^= a;
  }
  else
  {
  /* EOR.B #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<24;
  addr = get_eab[7](reg0);
  b = read_B(addr)<<24;
  EORB(s,a,b);
  write_B(addr,(u32)s>>24);
  }
}

static void l0_ADDb7(u32 reg0)
{
  /* ADD.B #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<24;
  addr = get_eab[7](reg0);
  b = read_B(addr)<<24;
  ADDB(s,a,b);
  write_B(addr,(u32)s>>24);
}

static void l0_SUBb7(u32 reg0)
{
  /* SUB.B #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<24;
  addr = get_eab[7](reg0);
  b = read_B(addr)<<24;
  SUBB(s,a,b);
  write_B(addr,(u32)s>>24);
}

static void l0_CMPb7(u32 reg0)
{
  /* CMP.B #imm,<Ae> */
  s32 a,b;
  u32 addr;
  a = get_nextw()<<24;
  addr = get_eab[7](reg0);
  b = read_B(addr)<<24;
  CMPB(a,b);
}

static void l0_ORw7(u32 reg0)
{
  if(reg0==4)
  {
    u32 a;
    a = get_nextw();
    reg68.sr |= a;
  }
  else
  {
  /* OR.W #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<16;
  addr = get_eaw[7](reg0);
  b = read_W(addr)<<16;
  ORW(s,a,b);
  write_W(addr,(u32)s>>16);
  }
}

static void l0_ANDw7(u32 reg0)
{
  if(reg0==4)
  {
    u32 a;
    a = get_nextw();
    reg68.sr &= a;
  }
  else
  {
  /* AND.W #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<16;
  addr = get_eaw[7](reg0);
  b = read_W(addr)<<16;
  ANDW(s,a,b);
  write_W(addr,(u32)s>>16);
  }
}

static void l0_EORw7(u32 reg0)
{
  if(reg0==4)
  {
    u32 a;
    a = get_nextw();
    reg68.sr ^= a;
  }
  else
  {
  /* EOR.W #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<16;
  addr = get_eaw[7](reg0);
  b = read_W(addr)<<16;
  EORW(s,a,b);
  write_W(addr,(u32)s>>16);
  }
}

static void l0_ADDw7(u32 reg0)
{
  /* ADD.W #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<16;
  addr = get_eaw[7](reg0);
  b = read_W(addr)<<16;
  ADDW(s,a,b);
  write_W(addr,(u32)s>>16);
}

static void l0_SUBw7(u32 reg0)
{
  /* SUB.W #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextw()<<16;
  addr = get_eaw[7](reg0);
  b = read_W(addr)<<16;
  SUBW(s,a,b);
  write_W(addr,(u32)s>>16);
}

static void l0_CMPw7(u32 reg0)
{
  /* CMP.W #imm,<Ae> */
  s32 a,b;
  u32 addr;
  a = get_nextw()<<16;
  addr = get_eaw[7](reg0);
  b = read_W(addr)<<16;
  CMPW(a,b);
}

static void l0_ORl7(u32 reg0)
{
  /* OR.L #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextl()<<0;
  addr = get_eal[7](reg0);
  b = read_L(addr)<<0;
  ORL(s,a,b);
  write_L(addr,(u32)s>>0);
}

static void l0_ANDl7(u32 reg0)
{
  /* AND.L #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextl()<<0;
  addr = get_eal[7](reg0);
  b = read_L(addr)<<0;
  ANDL(s,a,b);
  write_L(addr,(u32)s>>0);
}

static void l0_EORl7(u32 reg0)
{
  /* EOR.L #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextl()<<0;
  addr = get_eal[7](reg0);
  b = read_L(addr)<<0;
  EORL(s,a,b);
  write_L(addr,(u32)s>>0);
}

static void l0_ADDl7(u32 reg0)
{
  /* ADD.L #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextl()<<0;
  addr = get_eal[7](reg0);
  b = read_L(addr)<<0;
  ADDL(s,a,b);
  write_L(addr,(u32)s>>0);
}

static void l0_SUBl7(u32 reg0)
{
  /* SUB.L #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = get_nextl()<<0;
  addr = get_eal[7](reg0);
  b = read_L(addr)<<0;
  SUBL(s,a,b);
  write_L(addr,(u32)s>>0);
}

static void l0_CMPl7(u32 reg0)
{
  /* CMP.L #imm,<Ae> */
  s32 a,b;
  u32 addr;
  a = get_nextl()<<0;
  addr = get_eal[7](reg0);
  b = read_L(addr)<<0;
  CMPL(a,b);
}

static void (*line0_imm[8][32])(u32) =
{
/* OR */
  {
  l0_ORb0,l0_ill,l0_ORb2,l0_ORb3,l0_ORb4,l0_ORb5,l0_ORb6,l0_ORb7,
  l0_ORw0,l0_ill,l0_ORw2,l0_ORw3,l0_ORw4,l0_ORw5,l0_ORw6,l0_ORw7,
  l0_ORl0,l0_ill,l0_ORl2,l0_ORl3,l0_ORl4,l0_ORl5,l0_ORl6,l0_ORl7,
  l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,

  },
/* AND */
  {
  l0_ANDb0,l0_ill,l0_ANDb2,l0_ANDb3,l0_ANDb4,l0_ANDb5,l0_ANDb6,l0_ANDb7,
  l0_ANDw0,l0_ill,l0_ANDw2,l0_ANDw3,l0_ANDw4,l0_ANDw5,l0_ANDw6,l0_ANDw7,
  l0_ANDl0,l0_ill,l0_ANDl2,l0_ANDl3,l0_ANDl4,l0_ANDl5,l0_ANDl6,l0_ANDl7,
  l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,

  },
/* SUB */
  {
  l0_SUBb0,l0_ill,l0_SUBb2,l0_SUBb3,l0_SUBb4,l0_SUBb5,l0_SUBb6,l0_SUBb7,
  l0_SUBw0,l0_ill,l0_SUBw2,l0_SUBw3,l0_SUBw4,l0_SUBw5,l0_SUBw6,l0_SUBw7,
  l0_SUBl0,l0_ill,l0_SUBl2,l0_SUBl3,l0_SUBl4,l0_SUBl5,l0_SUBl6,l0_SUBl7,
  l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,

  },
/* ADD */
  {
  l0_ADDb0,l0_ill,l0_ADDb2,l0_ADDb3,l0_ADDb4,l0_ADDb5,l0_ADDb6,l0_ADDb7,
  l0_ADDw0,l0_ill,l0_ADDw2,l0_ADDw3,l0_ADDw4,l0_ADDw5,l0_ADDw6,l0_ADDw7,
  l0_ADDl0,l0_ill,l0_ADDl2,l0_ADDl3,l0_ADDl4,l0_ADDl5,l0_ADDl6,l0_ADDl7,
  l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,

  },
/* ? */
  {
  l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,
  l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,
  l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,
  l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,

  },
/* EOR */
  {
  l0_EORb0,l0_ill,l0_EORb2,l0_EORb3,l0_EORb4,l0_EORb5,l0_EORb6,l0_EORb7,
  l0_EORw0,l0_ill,l0_EORw2,l0_EORw3,l0_EORw4,l0_EORw5,l0_EORw6,l0_EORw7,
  l0_EORl0,l0_ill,l0_EORl2,l0_EORl3,l0_EORl4,l0_EORl5,l0_EORl6,l0_EORl7,
  l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,

  },
/* CMP */
  {
  l0_CMPb0,l0_ill,l0_CMPb2,l0_CMPb3,l0_CMPb4,l0_CMPb5,l0_CMPb6,l0_CMPb7,
  l0_CMPw0,l0_ill,l0_CMPw2,l0_CMPw3,l0_CMPw4,l0_CMPw5,l0_CMPw6,l0_CMPw7,
  l0_CMPl0,l0_ill,l0_CMPl2,l0_CMPl3,l0_CMPl4,l0_CMPl5,l0_CMPl6,l0_CMPl7,
  l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,

  },
/* ? */
  {
  l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,
  l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,
  l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,
  l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,l0_ill,

  },
};

void line000(u32 reg9, u32 reg0)
{
  if(reg9==4) BTST_reg(get_nextw(),reg0);
  else (line0_imm[reg9][0])(reg0);
}

void line001(u32 reg9, u32 reg0)
{
  if(reg9==4) BTST_mem(get_nextw(),1,reg0);
  else (line0_imm[reg9][1])(reg0);
}

void line002(u32 reg9, u32 reg0)
{
  if(reg9==4) BTST_mem(get_nextw(),2,reg0);
  else (line0_imm[reg9][2])(reg0);
}

void line003(u32 reg9, u32 reg0)
{
  if(reg9==4) BTST_mem(get_nextw(),3,reg0);
  else (line0_imm[reg9][3])(reg0);
}

void line004(u32 reg9, u32 reg0)
{
  if(reg9==4) BTST_mem(get_nextw(),4,reg0);
  else (line0_imm[reg9][4])(reg0);
}

void line005(u32 reg9, u32 reg0)
{
  if(reg9==4) BTST_mem(get_nextw(),5,reg0);
  else (line0_imm[reg9][5])(reg0);
}

void line006(u32 reg9, u32 reg0)
{
  if(reg9==4) BTST_mem(get_nextw(),6,reg0);
  else (line0_imm[reg9][6])(reg0);
}

void line007(u32 reg9, u32 reg0)
{
  if(reg9==4) BTST_mem(get_nextw(),7,reg0);
  else (line0_imm[reg9][7])(reg0);
}

void line008(u32 reg9, u32 reg0)
{
  if(reg9==4) BCHG_reg(get_nextw(),reg0);
  else (line0_imm[reg9][8])(reg0);
}

void line009(u32 reg9, u32 reg0)
{
  if(reg9==4) BCHG_mem(get_nextw(),1,reg0);
  else (line0_imm[reg9][9])(reg0);
}

void line00A(u32 reg9, u32 reg0)
{
  if(reg9==4) BCHG_mem(get_nextw(),2,reg0);
  else (line0_imm[reg9][10])(reg0);
}

void line00B(u32 reg9, u32 reg0)
{
  if(reg9==4) BCHG_mem(get_nextw(),3,reg0);
  else (line0_imm[reg9][11])(reg0);
}

void line00C(u32 reg9, u32 reg0)
{
  if(reg9==4) BCHG_mem(get_nextw(),4,reg0);
  else (line0_imm[reg9][12])(reg0);
}

void line00D(u32 reg9, u32 reg0)
{
  if(reg9==4) BCHG_mem(get_nextw(),5,reg0);
  else (line0_imm[reg9][13])(reg0);
}

void line00E(u32 reg9, u32 reg0)
{
  if(reg9==4) BCHG_mem(get_nextw(),6,reg0);
  else (line0_imm[reg9][14])(reg0);
}

void line00F(u32 reg9, u32 reg0)
{
  if(reg9==4) BCHG_mem(get_nextw(),7,reg0);
  else (line0_imm[reg9][15])(reg0);
}

void line010(u32 reg9, u32 reg0)
{
  if(reg9==4) BCLR_reg(get_nextw(),reg0);
  else (line0_imm[reg9][16])(reg0);
}

void line011(u32 reg9, u32 reg0)
{
  if(reg9==4) BCLR_mem(get_nextw(),1,reg0);
  else (line0_imm[reg9][17])(reg0);
}

void line012(u32 reg9, u32 reg0)
{
  if(reg9==4) BCLR_mem(get_nextw(),2,reg0);
  else (line0_imm[reg9][18])(reg0);
}

void line013(u32 reg9, u32 reg0)
{
  if(reg9==4) BCLR_mem(get_nextw(),3,reg0);
  else (line0_imm[reg9][19])(reg0);
}

void line014(u32 reg9, u32 reg0)
{
  if(reg9==4) BCLR_mem(get_nextw(),4,reg0);
  else (line0_imm[reg9][20])(reg0);
}

void line015(u32 reg9, u32 reg0)
{
  if(reg9==4) BCLR_mem(get_nextw(),5,reg0);
  else (line0_imm[reg9][21])(reg0);
}

void line016(u32 reg9, u32 reg0)
{
  if(reg9==4) BCLR_mem(get_nextw(),6,reg0);
  else (line0_imm[reg9][22])(reg0);
}

void line017(u32 reg9, u32 reg0)
{
  if(reg9==4) BCLR_mem(get_nextw(),7,reg0);
  else (line0_imm[reg9][23])(reg0);
}

void line018(u32 reg9, u32 reg0)
{
  if(reg9==4) BSET_reg(get_nextw(),reg0);
  else (line0_imm[reg9][24])(reg0);
}

void line019(u32 reg9, u32 reg0)
{
  if(reg9==4) BSET_mem(get_nextw(),1,reg0);
  else (line0_imm[reg9][25])(reg0);
}

void line01A(u32 reg9, u32 reg0)
{
  if(reg9==4) BSET_mem(get_nextw(),2,reg0);
  else (line0_imm[reg9][26])(reg0);
}

void line01B(u32 reg9, u32 reg0)
{
  if(reg9==4) BSET_mem(get_nextw(),3,reg0);
  else (line0_imm[reg9][27])(reg0);
}

void line01C(u32 reg9, u32 reg0)
{
  if(reg9==4) BSET_mem(get_nextw(),4,reg0);
  else (line0_imm[reg9][28])(reg0);
}

void line01D(u32 reg9, u32 reg0)
{
  if(reg9==4) BSET_mem(get_nextw(),5,reg0);
  else (line0_imm[reg9][29])(reg0);
}

void line01E(u32 reg9, u32 reg0)
{
  if(reg9==4) BSET_mem(get_nextw(),6,reg0);
  else (line0_imm[reg9][30])(reg0);
}

void line01F(u32 reg9, u32 reg0)
{
  if(reg9==4) BSET_mem(get_nextw(),7,reg0);
  else (line0_imm[reg9][31])(reg0);
}

void line020(u32 reg9, u32 reg0)
{
  /* BTST Dx,Dy */
  u32 a,b;
  a = reg68.d[reg0];
  b = reg68.d[reg9]&31;
  BTST(a,b);
  ADDCYCLE(2);
}

void line021(u32 reg9, u32 reg0)
{
  /* MOVEP.W d(An),Dn */
  u32 addr = reg68.a[reg0] + get_nextw();
  u32 a;
  a  =(u8)read_B(addr)<<8;
  a +=(u8)read_B(addr+=2)<<0;
  reg68.d[reg9] = (reg68.d[reg9]&0xFFFF0000) | a;
  ADDCYCLE(8);
}

void line022(u32 reg9, u32 reg0)
{
  /* BTST Dn,<Ae> */
  u32 a,b;
  u32 addr;
  addr = get_eab[2](reg0);
  a = read_B(addr);
  b = reg68.d[reg9]&7;
  BTST(a,b);
  ADDCYCLE(0);
}

void line023(u32 reg9, u32 reg0)
{
  /* BTST Dn,<Ae> */
  u32 a,b;
  u32 addr;
  addr = get_eab[3](reg0);
  a = read_B(addr);
  b = reg68.d[reg9]&7;
  BTST(a,b);
  ADDCYCLE(0);
}

void line024(u32 reg9, u32 reg0)
{
  /* BTST Dn,<Ae> */
  u32 a,b;
  u32 addr;
  addr = get_eab[4](reg0);
  a = read_B(addr);
  b = reg68.d[reg9]&7;
  BTST(a,b);
  ADDCYCLE(0);
}

void line025(u32 reg9, u32 reg0)
{
  /* BTST Dn,<Ae> */
  u32 a,b;
  u32 addr;
  addr = get_eab[5](reg0);
  a = read_B(addr);
  b = reg68.d[reg9]&7;
  BTST(a,b);
  ADDCYCLE(0);
}

void line026(u32 reg9, u32 reg0)
{
  /* BTST Dn,<Ae> */
  u32 a,b;
  u32 addr;
  addr = get_eab[6](reg0);
  a = read_B(addr);
  b = reg68.d[reg9]&7;
  BTST(a,b);
  ADDCYCLE(0);
}

void line027(u32 reg9, u32 reg0)
{
  /* BTST Dn,<Ae> */
  u32 a,b;
  u32 addr;
  addr = get_eab[7](reg0);
  a = read_B(addr);
  b = reg68.d[reg9]&7;
  BTST(a,b);
  ADDCYCLE(0);
}

void line028(u32 reg9, u32 reg0)
{
  /* BCHG Dx,Dy */
  u32 a,b;
  a = reg68.d[reg0];
  b = reg68.d[reg9]&31;
  BCHG(a,b);
  reg68.d[reg0] = a;
  ADDCYCLE(4);
}

void line029(u32 reg9, u32 reg0)
{
  /* MOVEP.L d(An),Dn */
  u32 addr = reg68.a[reg0] + get_nextw();
  u32 a;
  a  =(u8)read_B(addr)<<24;
  a +=(u8)read_B(addr+=2)<<16;
  a +=(u8)read_B(addr+=2)<<8;
  a +=(u8)read_B(addr+=2)<<0;
  reg68.d[reg9] = a;
  ADDCYCLE(16);
}

void line02A(u32 reg9, u32 reg0)
{
  /* BCHG Dn,<Ae> */
  u32 a,b;
  u32 addr;
  addr = get_eab[2](reg0);
  a = read_B(addr);
  b = reg68.d[reg9]&7;
  BCHG(a,b);
  write_B(addr,a);
  ADDCYCLE(4);
}

void line02B(u32 reg9, u32 reg0)
{
  /* BCHG Dn,<Ae> */
  u32 a,b;
  u32 addr;
  addr = get_eab[3](reg0);
  a = read_B(addr);
  b = reg68.d[reg9]&7;
  BCHG(a,b);
  write_B(addr,a);
  ADDCYCLE(4);
}

void line02C(u32 reg9, u32 reg0)
{
  /* BCHG Dn,<Ae> */
  u32 a,b;
  u32 addr;
  addr = get_eab[4](reg0);
  a = read_B(addr);
  b = reg68.d[reg9]&7;
  BCHG(a,b);
  write_B(addr,a);
  ADDCYCLE(4);
}

void line02D(u32 reg9, u32 reg0)
{
  /* BCHG Dn,<Ae> */
  u32 a,b;
  u32 addr;
  addr = get_eab[5](reg0);
  a = read_B(addr);
  b = reg68.d[reg9]&7;
  BCHG(a,b);
  write_B(addr,a);
  ADDCYCLE(4);
}

void line02E(u32 reg9, u32 reg0)
{
  /* BCHG Dn,<Ae> */
  u32 a,b;
  u32 addr;
  addr = get_eab[6](reg0);
  a = read_B(addr);
  b = reg68.d[reg9]&7;
  BCHG(a,b);
  write_B(addr,a);
  ADDCYCLE(4);
}

void line02F(u32 reg9, u32 reg0)
{
  /* BCHG Dn,<Ae> */
  u32 a,b;
  u32 addr;
  addr = get_eab[7](reg0);
  a = read_B(addr);
  b = reg68.d[reg9]&7;
  BCHG(a,b);
  write_B(addr,a);
  ADDCYCLE(4);
}

void line030(u32 reg9, u32 reg0)
{
  /* BCLR Dx,Dy */
  u32 a,b;
  a = reg68.d[reg0];
  b = reg68.d[reg9]&31;
  BCLR(a,b);
  reg68.d[reg0] = a;
  ADDCYCLE(6);
}

void line031(u32 reg9, u32 reg0)
{
  /* MOVEP.W Dn,d(An) */
  u32 addr = reg68.a[reg0] + get_nextw();
  u32 a;
  a = reg68.d[reg9];
  write_B(addr,a>>8);
  write_B(addr+=2,a>>0);
  ADDCYCLE(8);
}

void line032(u32 reg9, u32 reg0)
{
  /* BCLR Dn,<Ae> */
  u32 a,b;
  u32 addr;
  addr = get_eab[2](reg0);
  a = read_B(addr);
  b = reg68.d[reg9]&7;
  BCLR(a,b);
  write_B(addr,a);
  ADDCYCLE(4);
}

void line033(u32 reg9, u32 reg0)
{
  /* BCLR Dn,<Ae> */
  u32 a,b;
  u32 addr;
  addr = get_eab[3](reg0);
  a = read_B(addr);
  b = reg68.d[reg9]&7;
  BCLR(a,b);
  write_B(addr,a);
  ADDCYCLE(4);
}

void line034(u32 reg9, u32 reg0)
{
  /* BCLR Dn,<Ae> */
  u32 a,b;
  u32 addr;
  addr = get_eab[4](reg0);
  a = read_B(addr);
  b = reg68.d[reg9]&7;
  BCLR(a,b);
  write_B(addr,a);
  ADDCYCLE(4);
}

void line035(u32 reg9, u32 reg0)
{
  /* BCLR Dn,<Ae> */
  u32 a,b;
  u32 addr;
  addr = get_eab[5](reg0);
  a = read_B(addr);
  b = reg68.d[reg9]&7;
  BCLR(a,b);
  write_B(addr,a);
  ADDCYCLE(4);
}

void line036(u32 reg9, u32 reg0)
{
  /* BCLR Dn,<Ae> */
  u32 a,b;
  u32 addr;
  addr = get_eab[6](reg0);
  a = read_B(addr);
  b = reg68.d[reg9]&7;
  BCLR(a,b);
  write_B(addr,a);
  ADDCYCLE(4);
}

void line037(u32 reg9, u32 reg0)
{
  /* BCLR Dn,<Ae> */
  u32 a,b;
  u32 addr;
  addr = get_eab[7](reg0);
  a = read_B(addr);
  b = reg68.d[reg9]&7;
  BCLR(a,b);
  write_B(addr,a);
  ADDCYCLE(4);
}

void line038(u32 reg9, u32 reg0)
{
  /* BSET Dx,Dy */
  u32 a,b;
  a = reg68.d[reg0];
  b = reg68.d[reg9]&31;
  BSET(a,b);
  reg68.d[reg0] = a;
  ADDCYCLE(4);
}

void line039(u32 reg9, u32 reg0)
{
  /* MOVEP.L Dn,d(An) */
  u32 addr = reg68.a[reg0] + get_nextw();
  u32 a;
  a = reg68.d[reg9];
  write_B(addr,a>>24);
  write_B(addr+=2,a>>16);
  write_B(addr+=2,a>>8);
  write_B(addr+=2,a>>0);
  ADDCYCLE(16);
}

void line03A(u32 reg9, u32 reg0)
{
  /* BSET Dn,<Ae> */
  u32 a,b;
  u32 addr;
  addr = get_eab[2](reg0);
  a = read_B(addr);
  b = reg68.d[reg9]&7;
  BSET(a,b);
  write_B(addr,a);
  ADDCYCLE(4);
}

void line03B(u32 reg9, u32 reg0)
{
  /* BSET Dn,<Ae> */
  u32 a,b;
  u32 addr;
  addr = get_eab[3](reg0);
  a = read_B(addr);
  b = reg68.d[reg9]&7;
  BSET(a,b);
  write_B(addr,a);
  ADDCYCLE(4);
}

void line03C(u32 reg9, u32 reg0)
{
  /* BSET Dn,<Ae> */
  u32 a,b;
  u32 addr;
  addr = get_eab[4](reg0);
  a = read_B(addr);
  b = reg68.d[reg9]&7;
  BSET(a,b);
  write_B(addr,a);
  ADDCYCLE(4);
}

void line03D(u32 reg9, u32 reg0)
{
  /* BSET Dn,<Ae> */
  u32 a,b;
  u32 addr;
  addr = get_eab[5](reg0);
  a = read_B(addr);
  b = reg68.d[reg9]&7;
  BSET(a,b);
  write_B(addr,a);
  ADDCYCLE(4);
}

void line03E(u32 reg9, u32 reg0)
{
  /* BSET Dn,<Ae> */
  u32 a,b;
  u32 addr;
  addr = get_eab[6](reg0);
  a = read_B(addr);
  b = reg68.d[reg9]&7;
  BSET(a,b);
  write_B(addr,a);
  ADDCYCLE(4);
}

void line03F(u32 reg9, u32 reg0)
{
  /* BSET Dn,<Ae> */
  u32 a,b;
  u32 addr;
  addr = get_eab[7](reg0);
  a = read_B(addr);
  b = reg68.d[reg9]&7;
  BSET(a,b);
  write_B(addr,a);
  ADDCYCLE(4);
}

void line100(u32 reg9, u32 reg0)
{
  /* MOVE.B Dn,Dn */
  s32 a;
  a = reg68.d[reg0]<<24;
  reg68.d[reg9] = (reg68.d[reg9]&0xffffff00) + ((u32)a>>24);
  MOVE(a);
}

void line101(u32 reg9, u32 reg0)
{
  /* MOVE.B An,Dn */
  s32 a;
  a = reg68.a[reg0]<<24;
  reg68.d[reg9] = (reg68.d[reg9]&0xffffff00) + ((u32)a>>24);
  MOVE(a);
}

void line102(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,Dn */
  s32 a;
  u32 addr;
  addr = get_eab[2](reg0);
  a = read_B(addr)<<24;
  reg68.d[reg9] = (reg68.d[reg9]&0xffffff00) + ((u32)a>>24);
  MOVE(a);
}

void line103(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,Dn */
  s32 a;
  u32 addr;
  addr = get_eab[3](reg0);
  a = read_B(addr)<<24;
  reg68.d[reg9] = (reg68.d[reg9]&0xffffff00) + ((u32)a>>24);
  MOVE(a);
}

void line104(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,Dn */
  s32 a;
  u32 addr;
  addr = get_eab[4](reg0);
  a = read_B(addr)<<24;
  reg68.d[reg9] = (reg68.d[reg9]&0xffffff00) + ((u32)a>>24);
  MOVE(a);
}

void line105(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,Dn */
  s32 a;
  u32 addr;
  addr = get_eab[5](reg0);
  a = read_B(addr)<<24;
  reg68.d[reg9] = (reg68.d[reg9]&0xffffff00) + ((u32)a>>24);
  MOVE(a);
}

void line106(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,Dn */
  s32 a;
  u32 addr;
  addr = get_eab[6](reg0);
  a = read_B(addr)<<24;
  reg68.d[reg9] = (reg68.d[reg9]&0xffffff00) + ((u32)a>>24);
  MOVE(a);
}

void line107(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,Dn */
  s32 a;
  u32 addr;
  addr = get_eab[7](reg0);
  a = read_B(addr)<<24;
  reg68.d[reg9] = (reg68.d[reg9]&0xffffff00) + ((u32)a>>24);
  MOVE(a);
}

void line108(u32 reg9, u32 reg0)
{
  /* MOVE.B Dn,An */
  s32 a;
  a = reg68.d[reg0]<<24;
  reg68.a[reg9] = a>>24;
}

void line109(u32 reg9, u32 reg0)
{
  /* MOVE.B An,An */
  s32 a;
  a = reg68.a[reg0]<<24;
  reg68.a[reg9] = a>>24;
}

void line10A(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,An */
  s32 a;
  u32 addr;
  addr = get_eab[2](reg0);
  a = read_B(addr)<<24;
  reg68.a[reg9] = a>>24;
}

void line10B(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,An */
  s32 a;
  u32 addr;
  addr = get_eab[3](reg0);
  a = read_B(addr)<<24;
  reg68.a[reg9] = a>>24;
}

void line10C(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,An */
  s32 a;
  u32 addr;
  addr = get_eab[4](reg0);
  a = read_B(addr)<<24;
  reg68.a[reg9] = a>>24;
}

void line10D(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,An */
  s32 a;
  u32 addr;
  addr = get_eab[5](reg0);
  a = read_B(addr)<<24;
  reg68.a[reg9] = a>>24;
}

void line10E(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,An */
  s32 a;
  u32 addr;
  addr = get_eab[6](reg0);
  a = read_B(addr)<<24;
  reg68.a[reg9] = a>>24;
}

void line10F(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,An */
  s32 a;
  u32 addr;
  addr = get_eab[7](reg0);
  a = read_B(addr)<<24;
  reg68.a[reg9] = a>>24;
}

void line110(u32 reg9, u32 reg0)
{
  /* MOVE.B Dn,<Ae> */
  s32 a;
  u32 addr;
  a = reg68.d[reg0]<<24;
  addr = get_eab[2](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line111(u32 reg9, u32 reg0)
{
  /* MOVE.B An,<Ae> */
  s32 a;
  u32 addr;
  a = reg68.a[reg0]<<24;
  addr = get_eab[2](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line112(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eab[2](reg0);
  a = read_B(addr)<<24;
  addr = get_eab[2](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line113(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eab[3](reg0);
  a = read_B(addr)<<24;
  addr = get_eab[2](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line114(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eab[4](reg0);
  a = read_B(addr)<<24;
  addr = get_eab[2](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line115(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eab[5](reg0);
  a = read_B(addr)<<24;
  addr = get_eab[2](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line116(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eab[6](reg0);
  a = read_B(addr)<<24;
  addr = get_eab[2](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line117(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eab[7](reg0);
  a = read_B(addr)<<24;
  addr = get_eab[2](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line118(u32 reg9, u32 reg0)
{
  /* MOVE.B Dn,<Ae> */
  s32 a;
  u32 addr;
  a = reg68.d[reg0]<<24;
  addr = get_eab[3](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line119(u32 reg9, u32 reg0)
{
  /* MOVE.B An,<Ae> */
  s32 a;
  u32 addr;
  a = reg68.a[reg0]<<24;
  addr = get_eab[3](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line11A(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eab[2](reg0);
  a = read_B(addr)<<24;
  addr = get_eab[3](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line11B(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eab[3](reg0);
  a = read_B(addr)<<24;
  addr = get_eab[3](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line11C(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eab[4](reg0);
  a = read_B(addr)<<24;
  addr = get_eab[3](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line11D(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eab[5](reg0);
  a = read_B(addr)<<24;
  addr = get_eab[3](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line11E(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eab[6](reg0);
  a = read_B(addr)<<24;
  addr = get_eab[3](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line11F(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eab[7](reg0);
  a = read_B(addr)<<24;
  addr = get_eab[3](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line120(u32 reg9, u32 reg0)
{
  /* MOVE.B Dn,<Ae> */
  s32 a;
  u32 addr;
  a = reg68.d[reg0]<<24;
  addr = get_eab[4](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line121(u32 reg9, u32 reg0)
{
  /* MOVE.B An,<Ae> */
  s32 a;
  u32 addr;
  a = reg68.a[reg0]<<24;
  addr = get_eab[4](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line122(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eab[2](reg0);
  a = read_B(addr)<<24;
  addr = get_eab[4](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line123(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eab[3](reg0);
  a = read_B(addr)<<24;
  addr = get_eab[4](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line124(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eab[4](reg0);
  a = read_B(addr)<<24;
  addr = get_eab[4](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line125(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eab[5](reg0);
  a = read_B(addr)<<24;
  addr = get_eab[4](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line126(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eab[6](reg0);
  a = read_B(addr)<<24;
  addr = get_eab[4](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line127(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eab[7](reg0);
  a = read_B(addr)<<24;
  addr = get_eab[4](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line128(u32 reg9, u32 reg0)
{
  /* MOVE.B Dn,<Ae> */
  s32 a;
  u32 addr;
  a = reg68.d[reg0]<<24;
  addr = get_eab[5](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line129(u32 reg9, u32 reg0)
{
  /* MOVE.B An,<Ae> */
  s32 a;
  u32 addr;
  a = reg68.a[reg0]<<24;
  addr = get_eab[5](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line12A(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eab[2](reg0);
  a = read_B(addr)<<24;
  addr = get_eab[5](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line12B(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eab[3](reg0);
  a = read_B(addr)<<24;
  addr = get_eab[5](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line12C(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eab[4](reg0);
  a = read_B(addr)<<24;
  addr = get_eab[5](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line12D(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eab[5](reg0);
  a = read_B(addr)<<24;
  addr = get_eab[5](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line12E(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eab[6](reg0);
  a = read_B(addr)<<24;
  addr = get_eab[5](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line12F(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eab[7](reg0);
  a = read_B(addr)<<24;
  addr = get_eab[5](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line130(u32 reg9, u32 reg0)
{
  /* MOVE.B Dn,<Ae> */
  s32 a;
  u32 addr;
  a = reg68.d[reg0]<<24;
  addr = get_eab[6](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line131(u32 reg9, u32 reg0)
{
  /* MOVE.B An,<Ae> */
  s32 a;
  u32 addr;
  a = reg68.a[reg0]<<24;
  addr = get_eab[6](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line132(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eab[2](reg0);
  a = read_B(addr)<<24;
  addr = get_eab[6](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line133(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eab[3](reg0);
  a = read_B(addr)<<24;
  addr = get_eab[6](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line134(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eab[4](reg0);
  a = read_B(addr)<<24;
  addr = get_eab[6](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line135(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eab[5](reg0);
  a = read_B(addr)<<24;
  addr = get_eab[6](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line136(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eab[6](reg0);
  a = read_B(addr)<<24;
  addr = get_eab[6](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line137(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eab[7](reg0);
  a = read_B(addr)<<24;
  addr = get_eab[6](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line138(u32 reg9, u32 reg0)
{
  /* MOVE.B Dn,<Ae> */
  s32 a;
  u32 addr;
  a = reg68.d[reg0]<<24;
  addr = get_eab[7](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line139(u32 reg9, u32 reg0)
{
  /* MOVE.B An,<Ae> */
  s32 a;
  u32 addr;
  a = reg68.a[reg0]<<24;
  addr = get_eab[7](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line13A(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eab[2](reg0);
  a = read_B(addr)<<24;
  addr = get_eab[7](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line13B(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eab[3](reg0);
  a = read_B(addr)<<24;
  addr = get_eab[7](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line13C(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eab[4](reg0);
  a = read_B(addr)<<24;
  addr = get_eab[7](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line13D(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eab[5](reg0);
  a = read_B(addr)<<24;
  addr = get_eab[7](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line13E(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eab[6](reg0);
  a = read_B(addr)<<24;
  addr = get_eab[7](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line13F(u32 reg9, u32 reg0)
{
  /* MOVE.B <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eab[7](reg0);
  a = read_B(addr)<<24;
  addr = get_eab[7](reg9);
  write_B(addr,(u32)a>>24);
  MOVE(a);
}

void line200(u32 reg9, u32 reg0)
{
  /* MOVE.L Dn,Dn */
  s32 a;
  a = reg68.d[reg0]<<0;
  reg68.d[reg9] = (reg68.d[reg9]&0) + ((u32)a>>0);
  MOVE(a);
}

void line201(u32 reg9, u32 reg0)
{
  /* MOVE.L An,Dn */
  s32 a;
  a = reg68.a[reg0]<<0;
  reg68.d[reg9] = (reg68.d[reg9]&0) + ((u32)a>>0);
  MOVE(a);
}

void line202(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,Dn */
  s32 a;
  u32 addr;
  addr = get_eal[2](reg0);
  a = read_L(addr)<<0;
  reg68.d[reg9] = (reg68.d[reg9]&0) + ((u32)a>>0);
  MOVE(a);
}

void line203(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,Dn */
  s32 a;
  u32 addr;
  addr = get_eal[3](reg0);
  a = read_L(addr)<<0;
  reg68.d[reg9] = (reg68.d[reg9]&0) + ((u32)a>>0);
  MOVE(a);
}

void line204(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,Dn */
  s32 a;
  u32 addr;
  addr = get_eal[4](reg0);
  a = read_L(addr)<<0;
  reg68.d[reg9] = (reg68.d[reg9]&0) + ((u32)a>>0);
  MOVE(a);
}

void line205(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,Dn */
  s32 a;
  u32 addr;
  addr = get_eal[5](reg0);
  a = read_L(addr)<<0;
  reg68.d[reg9] = (reg68.d[reg9]&0) + ((u32)a>>0);
  MOVE(a);
}

void line206(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,Dn */
  s32 a;
  u32 addr;
  addr = get_eal[6](reg0);
  a = read_L(addr)<<0;
  reg68.d[reg9] = (reg68.d[reg9]&0) + ((u32)a>>0);
  MOVE(a);
}

void line207(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,Dn */
  s32 a;
  u32 addr;
  addr = get_eal[7](reg0);
  a = read_L(addr)<<0;
  reg68.d[reg9] = (reg68.d[reg9]&0) + ((u32)a>>0);
  MOVE(a);
}

void line208(u32 reg9, u32 reg0)
{
  /* MOVE.L Dn,An */
  s32 a;
  a = reg68.d[reg0]<<0;
  reg68.a[reg9] = a>>0;
}

void line209(u32 reg9, u32 reg0)
{
  /* MOVE.L An,An */
  s32 a;
  a = reg68.a[reg0]<<0;
  reg68.a[reg9] = a>>0;
}

void line20A(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,An */
  s32 a;
  u32 addr;
  addr = get_eal[2](reg0);
  a = read_L(addr)<<0;
  reg68.a[reg9] = a>>0;
}

void line20B(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,An */
  s32 a;
  u32 addr;
  addr = get_eal[3](reg0);
  a = read_L(addr)<<0;
  reg68.a[reg9] = a>>0;
}

void line20C(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,An */
  s32 a;
  u32 addr;
  addr = get_eal[4](reg0);
  a = read_L(addr)<<0;
  reg68.a[reg9] = a>>0;
}

void line20D(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,An */
  s32 a;
  u32 addr;
  addr = get_eal[5](reg0);
  a = read_L(addr)<<0;
  reg68.a[reg9] = a>>0;
}

void line20E(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,An */
  s32 a;
  u32 addr;
  addr = get_eal[6](reg0);
  a = read_L(addr)<<0;
  reg68.a[reg9] = a>>0;
}

void line20F(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,An */
  s32 a;
  u32 addr;
  addr = get_eal[7](reg0);
  a = read_L(addr)<<0;
  reg68.a[reg9] = a>>0;
}

void line210(u32 reg9, u32 reg0)
{
  /* MOVE.L Dn,<Ae> */
  s32 a;
  u32 addr;
  a = reg68.d[reg0]<<0;
  addr = get_eal[2](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line211(u32 reg9, u32 reg0)
{
  /* MOVE.L An,<Ae> */
  s32 a;
  u32 addr;
  a = reg68.a[reg0]<<0;
  addr = get_eal[2](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line212(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eal[2](reg0);
  a = read_L(addr)<<0;
  addr = get_eal[2](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line213(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eal[3](reg0);
  a = read_L(addr)<<0;
  addr = get_eal[2](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line214(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eal[4](reg0);
  a = read_L(addr)<<0;
  addr = get_eal[2](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line215(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eal[5](reg0);
  a = read_L(addr)<<0;
  addr = get_eal[2](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line216(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eal[6](reg0);
  a = read_L(addr)<<0;
  addr = get_eal[2](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line217(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eal[7](reg0);
  a = read_L(addr)<<0;
  addr = get_eal[2](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line218(u32 reg9, u32 reg0)
{
  /* MOVE.L Dn,<Ae> */
  s32 a;
  u32 addr;
  a = reg68.d[reg0]<<0;
  addr = get_eal[3](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line219(u32 reg9, u32 reg0)
{
  /* MOVE.L An,<Ae> */
  s32 a;
  u32 addr;
  a = reg68.a[reg0]<<0;
  addr = get_eal[3](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line21A(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eal[2](reg0);
  a = read_L(addr)<<0;
  addr = get_eal[3](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line21B(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eal[3](reg0);
  a = read_L(addr)<<0;
  addr = get_eal[3](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line21C(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eal[4](reg0);
  a = read_L(addr)<<0;
  addr = get_eal[3](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line21D(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eal[5](reg0);
  a = read_L(addr)<<0;
  addr = get_eal[3](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line21E(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eal[6](reg0);
  a = read_L(addr)<<0;
  addr = get_eal[3](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line21F(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eal[7](reg0);
  a = read_L(addr)<<0;
  addr = get_eal[3](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line220(u32 reg9, u32 reg0)
{
  /* MOVE.L Dn,<Ae> */
  s32 a;
  u32 addr;
  a = reg68.d[reg0]<<0;
  addr = get_eal[4](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line221(u32 reg9, u32 reg0)
{
  /* MOVE.L An,<Ae> */
  s32 a;
  u32 addr;
  a = reg68.a[reg0]<<0;
  addr = get_eal[4](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line222(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eal[2](reg0);
  a = read_L(addr)<<0;
  addr = get_eal[4](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line223(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eal[3](reg0);
  a = read_L(addr)<<0;
  addr = get_eal[4](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line224(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eal[4](reg0);
  a = read_L(addr)<<0;
  addr = get_eal[4](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line225(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eal[5](reg0);
  a = read_L(addr)<<0;
  addr = get_eal[4](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line226(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eal[6](reg0);
  a = read_L(addr)<<0;
  addr = get_eal[4](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line227(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eal[7](reg0);
  a = read_L(addr)<<0;
  addr = get_eal[4](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line228(u32 reg9, u32 reg0)
{
  /* MOVE.L Dn,<Ae> */
  s32 a;
  u32 addr;
  a = reg68.d[reg0]<<0;
  addr = get_eal[5](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line229(u32 reg9, u32 reg0)
{
  /* MOVE.L An,<Ae> */
  s32 a;
  u32 addr;
  a = reg68.a[reg0]<<0;
  addr = get_eal[5](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line22A(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eal[2](reg0);
  a = read_L(addr)<<0;
  addr = get_eal[5](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line22B(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eal[3](reg0);
  a = read_L(addr)<<0;
  addr = get_eal[5](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line22C(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eal[4](reg0);
  a = read_L(addr)<<0;
  addr = get_eal[5](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line22D(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eal[5](reg0);
  a = read_L(addr)<<0;
  addr = get_eal[5](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line22E(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eal[6](reg0);
  a = read_L(addr)<<0;
  addr = get_eal[5](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line22F(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eal[7](reg0);
  a = read_L(addr)<<0;
  addr = get_eal[5](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line230(u32 reg9, u32 reg0)
{
  /* MOVE.L Dn,<Ae> */
  s32 a;
  u32 addr;
  a = reg68.d[reg0]<<0;
  addr = get_eal[6](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line231(u32 reg9, u32 reg0)
{
  /* MOVE.L An,<Ae> */
  s32 a;
  u32 addr;
  a = reg68.a[reg0]<<0;
  addr = get_eal[6](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line232(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eal[2](reg0);
  a = read_L(addr)<<0;
  addr = get_eal[6](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line233(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eal[3](reg0);
  a = read_L(addr)<<0;
  addr = get_eal[6](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line234(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eal[4](reg0);
  a = read_L(addr)<<0;
  addr = get_eal[6](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line235(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eal[5](reg0);
  a = read_L(addr)<<0;
  addr = get_eal[6](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line236(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eal[6](reg0);
  a = read_L(addr)<<0;
  addr = get_eal[6](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line237(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eal[7](reg0);
  a = read_L(addr)<<0;
  addr = get_eal[6](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line238(u32 reg9, u32 reg0)
{
  /* MOVE.L Dn,<Ae> */
  s32 a;
  u32 addr;
  a = reg68.d[reg0]<<0;
  addr = get_eal[7](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line239(u32 reg9, u32 reg0)
{
  /* MOVE.L An,<Ae> */
  s32 a;
  u32 addr;
  a = reg68.a[reg0]<<0;
  addr = get_eal[7](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line23A(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eal[2](reg0);
  a = read_L(addr)<<0;
  addr = get_eal[7](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line23B(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eal[3](reg0);
  a = read_L(addr)<<0;
  addr = get_eal[7](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line23C(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eal[4](reg0);
  a = read_L(addr)<<0;
  addr = get_eal[7](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line23D(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eal[5](reg0);
  a = read_L(addr)<<0;
  addr = get_eal[7](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line23E(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eal[6](reg0);
  a = read_L(addr)<<0;
  addr = get_eal[7](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line23F(u32 reg9, u32 reg0)
{
  /* MOVE.L <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eal[7](reg0);
  a = read_L(addr)<<0;
  addr = get_eal[7](reg9);
  write_L(addr,(u32)a>>0);
  MOVE(a);
}

void line300(u32 reg9, u32 reg0)
{
  /* MOVE.W Dn,Dn */
  s32 a;
  a = reg68.d[reg0]<<16;
  reg68.d[reg9] = (reg68.d[reg9]&0xffff0000) + ((u32)a>>16);
  MOVE(a);
}

void line301(u32 reg9, u32 reg0)
{
  /* MOVE.W An,Dn */
  s32 a;
  a = reg68.a[reg0]<<16;
  reg68.d[reg9] = (reg68.d[reg9]&0xffff0000) + ((u32)a>>16);
  MOVE(a);
}

void line302(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,Dn */
  s32 a;
  u32 addr;
  addr = get_eaw[2](reg0);
  a = read_W(addr)<<16;
  reg68.d[reg9] = (reg68.d[reg9]&0xffff0000) + ((u32)a>>16);
  MOVE(a);
}

void line303(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,Dn */
  s32 a;
  u32 addr;
  addr = get_eaw[3](reg0);
  a = read_W(addr)<<16;
  reg68.d[reg9] = (reg68.d[reg9]&0xffff0000) + ((u32)a>>16);
  MOVE(a);
}

void line304(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,Dn */
  s32 a;
  u32 addr;
  addr = get_eaw[4](reg0);
  a = read_W(addr)<<16;
  reg68.d[reg9] = (reg68.d[reg9]&0xffff0000) + ((u32)a>>16);
  MOVE(a);
}

void line305(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,Dn */
  s32 a;
  u32 addr;
  addr = get_eaw[5](reg0);
  a = read_W(addr)<<16;
  reg68.d[reg9] = (reg68.d[reg9]&0xffff0000) + ((u32)a>>16);
  MOVE(a);
}

void line306(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,Dn */
  s32 a;
  u32 addr;
  addr = get_eaw[6](reg0);
  a = read_W(addr)<<16;
  reg68.d[reg9] = (reg68.d[reg9]&0xffff0000) + ((u32)a>>16);
  MOVE(a);
}

void line307(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,Dn */
  s32 a;
  u32 addr;
  addr = get_eaw[7](reg0);
  a = read_W(addr)<<16;
  reg68.d[reg9] = (reg68.d[reg9]&0xffff0000) + ((u32)a>>16);
  MOVE(a);
}

void line308(u32 reg9, u32 reg0)
{
  /* MOVE.W Dn,An */
  s32 a;
  a = reg68.d[reg0]<<16;
  reg68.a[reg9] = a>>16;
}

void line309(u32 reg9, u32 reg0)
{
  /* MOVE.W An,An */
  s32 a;
  a = reg68.a[reg0]<<16;
  reg68.a[reg9] = a>>16;
}

void line30A(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,An */
  s32 a;
  u32 addr;
  addr = get_eaw[2](reg0);
  a = read_W(addr)<<16;
  reg68.a[reg9] = a>>16;
}

void line30B(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,An */
  s32 a;
  u32 addr;
  addr = get_eaw[3](reg0);
  a = read_W(addr)<<16;
  reg68.a[reg9] = a>>16;
}

void line30C(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,An */
  s32 a;
  u32 addr;
  addr = get_eaw[4](reg0);
  a = read_W(addr)<<16;
  reg68.a[reg9] = a>>16;
}

void line30D(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,An */
  s32 a;
  u32 addr;
  addr = get_eaw[5](reg0);
  a = read_W(addr)<<16;
  reg68.a[reg9] = a>>16;
}

void line30E(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,An */
  s32 a;
  u32 addr;
  addr = get_eaw[6](reg0);
  a = read_W(addr)<<16;
  reg68.a[reg9] = a>>16;
}

void line30F(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,An */
  s32 a;
  u32 addr;
  addr = get_eaw[7](reg0);
  a = read_W(addr)<<16;
  reg68.a[reg9] = a>>16;
}

void line310(u32 reg9, u32 reg0)
{
  /* MOVE.W Dn,<Ae> */
  s32 a;
  u32 addr;
  a = reg68.d[reg0]<<16;
  addr = get_eaw[2](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line311(u32 reg9, u32 reg0)
{
  /* MOVE.W An,<Ae> */
  s32 a;
  u32 addr;
  a = reg68.a[reg0]<<16;
  addr = get_eaw[2](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line312(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eaw[2](reg0);
  a = read_W(addr)<<16;
  addr = get_eaw[2](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line313(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eaw[3](reg0);
  a = read_W(addr)<<16;
  addr = get_eaw[2](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line314(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eaw[4](reg0);
  a = read_W(addr)<<16;
  addr = get_eaw[2](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line315(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eaw[5](reg0);
  a = read_W(addr)<<16;
  addr = get_eaw[2](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line316(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eaw[6](reg0);
  a = read_W(addr)<<16;
  addr = get_eaw[2](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line317(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eaw[7](reg0);
  a = read_W(addr)<<16;
  addr = get_eaw[2](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line318(u32 reg9, u32 reg0)
{
  /* MOVE.W Dn,<Ae> */
  s32 a;
  u32 addr;
  a = reg68.d[reg0]<<16;
  addr = get_eaw[3](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line319(u32 reg9, u32 reg0)
{
  /* MOVE.W An,<Ae> */
  s32 a;
  u32 addr;
  a = reg68.a[reg0]<<16;
  addr = get_eaw[3](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line31A(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eaw[2](reg0);
  a = read_W(addr)<<16;
  addr = get_eaw[3](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line31B(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eaw[3](reg0);
  a = read_W(addr)<<16;
  addr = get_eaw[3](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line31C(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eaw[4](reg0);
  a = read_W(addr)<<16;
  addr = get_eaw[3](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line31D(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eaw[5](reg0);
  a = read_W(addr)<<16;
  addr = get_eaw[3](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line31E(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eaw[6](reg0);
  a = read_W(addr)<<16;
  addr = get_eaw[3](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line31F(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eaw[7](reg0);
  a = read_W(addr)<<16;
  addr = get_eaw[3](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line320(u32 reg9, u32 reg0)
{
  /* MOVE.W Dn,<Ae> */
  s32 a;
  u32 addr;
  a = reg68.d[reg0]<<16;
  addr = get_eaw[4](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line321(u32 reg9, u32 reg0)
{
  /* MOVE.W An,<Ae> */
  s32 a;
  u32 addr;
  a = reg68.a[reg0]<<16;
  addr = get_eaw[4](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line322(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eaw[2](reg0);
  a = read_W(addr)<<16;
  addr = get_eaw[4](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line323(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eaw[3](reg0);
  a = read_W(addr)<<16;
  addr = get_eaw[4](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line324(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eaw[4](reg0);
  a = read_W(addr)<<16;
  addr = get_eaw[4](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line325(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eaw[5](reg0);
  a = read_W(addr)<<16;
  addr = get_eaw[4](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line326(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eaw[6](reg0);
  a = read_W(addr)<<16;
  addr = get_eaw[4](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line327(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eaw[7](reg0);
  a = read_W(addr)<<16;
  addr = get_eaw[4](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line328(u32 reg9, u32 reg0)
{
  /* MOVE.W Dn,<Ae> */
  s32 a;
  u32 addr;
  a = reg68.d[reg0]<<16;
  addr = get_eaw[5](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line329(u32 reg9, u32 reg0)
{
  /* MOVE.W An,<Ae> */
  s32 a;
  u32 addr;
  a = reg68.a[reg0]<<16;
  addr = get_eaw[5](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line32A(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eaw[2](reg0);
  a = read_W(addr)<<16;
  addr = get_eaw[5](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line32B(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eaw[3](reg0);
  a = read_W(addr)<<16;
  addr = get_eaw[5](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line32C(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eaw[4](reg0);
  a = read_W(addr)<<16;
  addr = get_eaw[5](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line32D(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eaw[5](reg0);
  a = read_W(addr)<<16;
  addr = get_eaw[5](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line32E(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eaw[6](reg0);
  a = read_W(addr)<<16;
  addr = get_eaw[5](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line32F(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eaw[7](reg0);
  a = read_W(addr)<<16;
  addr = get_eaw[5](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line330(u32 reg9, u32 reg0)
{
  /* MOVE.W Dn,<Ae> */
  s32 a;
  u32 addr;
  a = reg68.d[reg0]<<16;
  addr = get_eaw[6](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line331(u32 reg9, u32 reg0)
{
  /* MOVE.W An,<Ae> */
  s32 a;
  u32 addr;
  a = reg68.a[reg0]<<16;
  addr = get_eaw[6](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line332(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eaw[2](reg0);
  a = read_W(addr)<<16;
  addr = get_eaw[6](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line333(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eaw[3](reg0);
  a = read_W(addr)<<16;
  addr = get_eaw[6](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line334(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eaw[4](reg0);
  a = read_W(addr)<<16;
  addr = get_eaw[6](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line335(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eaw[5](reg0);
  a = read_W(addr)<<16;
  addr = get_eaw[6](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line336(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eaw[6](reg0);
  a = read_W(addr)<<16;
  addr = get_eaw[6](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line337(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eaw[7](reg0);
  a = read_W(addr)<<16;
  addr = get_eaw[6](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line338(u32 reg9, u32 reg0)
{
  /* MOVE.W Dn,<Ae> */
  s32 a;
  u32 addr;
  a = reg68.d[reg0]<<16;
  addr = get_eaw[7](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line339(u32 reg9, u32 reg0)
{
  /* MOVE.W An,<Ae> */
  s32 a;
  u32 addr;
  a = reg68.a[reg0]<<16;
  addr = get_eaw[7](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line33A(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eaw[2](reg0);
  a = read_W(addr)<<16;
  addr = get_eaw[7](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line33B(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eaw[3](reg0);
  a = read_W(addr)<<16;
  addr = get_eaw[7](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line33C(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eaw[4](reg0);
  a = read_W(addr)<<16;
  addr = get_eaw[7](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line33D(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eaw[5](reg0);
  a = read_W(addr)<<16;
  addr = get_eaw[7](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line33E(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eaw[6](reg0);
  a = read_W(addr)<<16;
  addr = get_eaw[7](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

void line33F(u32 reg9, u32 reg0)
{
  /* MOVE.W <Ae>,<Ae> */
  s32 a;
  u32 addr;
  addr = get_eaw[7](reg0);
  a = read_W(addr)<<16;
  addr = get_eaw[7](reg9);
  write_W(addr,(u32)a>>16);
  MOVE(a);
}

static void funky4_m6_0(void)
{
  RESET;
}

static void funky4_m6_1(void)
{
  NOP;
}

static void funky4_m6_2(void)
{
  STOP;
}

static void funky4_m6_3(void)
{
  RTE;
}

static void funky4_m6_4(void)
{
  ILLEGAL;
}

static void funky4_m6_5(void)
{
  RTS;
}

static void funky4_m6_6(void)
{
  TRAPV;
}

static void funky4_m6_7(void)
{
  RTR;
}


static void (*funky4_m6_func[8])(void) =
{ funky4_m6_0,funky4_m6_1,funky4_m6_2,funky4_m6_3,funky4_m6_4,funky4_m6_5,funky4_m6_6,funky4_m6_7, };

static void funky4_m0(u32 reg0)
{
  s32 a = (0<<3)+reg0;
  TRAP(a);
}

static void funky4_m1(u32 reg0)
{
  s32 a = (1<<3)+reg0;
  TRAP(a);
}

static void funky4_m2(u32 reg0)
{
  LINK(reg0);
}

static void funky4_m3(u32 reg0)
{
  UNLK(reg0);
}

static void funky4_m4(u32 reg0)
{
  reg68.usp = reg68.a[reg0];
}

static void funky4_m5(u32 reg0)
{
  reg68.a[reg0] = reg68.usp;
}

static void funky4_m6(u32 reg0)
{
  (funky4_m6_func[reg0])();
}

static void funky4_m7(u32 reg0)
{
  ILLEGAL;
}

static void (*funky4_func[8])(u32) =
{ funky4_m0,funky4_m1,funky4_m2,funky4_m3,funky4_m4,funky4_m5,funky4_m6,funky4_m7,
};

static void movemregw(u32 mode, u32 reg0)
{
  u32 m = (u16)get_nextw(), addr;
  s32 *r = reg68.d;
  addr = get_eaw[mode](reg0);
  for(; m; r++, m>>=1)
    if(m&1){ *r=(s32)read_W(addr); addr+=2; }
  if(mode==3) reg68.a[reg0] = addr;
}

static void movemregl(u32 mode, u32 reg0)
{
  u32 m = (u16)get_nextw(), addr;
  s32 *r = reg68.d;
  addr = get_eal[mode](reg0);
  for(; m; r++, m>>=1)
    if(m&1){ *r=(s32)read_L(addr); addr+=4; }
  if(mode==3) reg68.a[reg0] = addr;
}

static void movemmemw(u32 mode, u32 reg0)
{
  u32 m = (u16)get_nextw(), addr;
  if(mode==4)
  {
    s32 *r = reg68.a+7;
    addr = get_eaw[3](reg0);
    for(; m; r--, m>>=1)
      if(m&1) write_W(addr-=2,*r);
    reg68.a[reg0] = addr;
  }
  else
  {
    s32 *r = reg68.d;
    addr = get_eaw[mode](reg0);
    for(; m; r++, m>>=1)
      if(m&1){ write_W(addr,*r); addr+=2; }
  }
}

static void movemmeml(u32 mode, u32 reg0)
{
  u32 m = (u16)get_nextw(), addr;
  if(mode==4)
  {
    s32 *r = reg68.a+7;
    addr = get_eal[3](reg0);
    for(; m; r--, m>>=1)
      if(m&1) write_L(addr-=4,*r);
    reg68.a[reg0] = addr;
  }
  else
  {
    s32 *r = reg68.d;
    addr = get_eal[mode](reg0);
    for(; m; r++, m>>=1)
      if(m&1){ write_L(addr,*r); addr+=4; }
  }
}

void line4_r0_s0(u32 mode, u32 reg0)
{
  /* NEGX.B <Ae> */
  if(mode<2)
  {
    s32 s;
    s32 a=reg68.d[reg0]<<24;
    NEGXB(s,a);
    reg68.d[reg0] = (reg68.d[reg0]&0xffffff00) | (u32)s>>24;
  }
  else
  {
    u32 addr=get_eab[mode](reg0);
    s32 s,a;
    a=read_B(addr)<<24;
    NEGXB(s,a);
    write_B(addr,(u32)s>>24);
  }
}

void line4_r0_s1(u32 mode, u32 reg0)
{
  /* NEGX.W <Ae> */
  if(mode<2)
  {
    s32 s;
    s32 a=reg68.d[reg0]<<16;
    NEGXW(s,a);
    reg68.d[reg0] = (reg68.d[reg0]&0xffff0000) | (u32)s>>16;
  }
  else
  {
    u32 addr=get_eaw[mode](reg0);
    s32 s,a;
    a=read_W(addr)<<16;
    NEGXW(s,a);
    write_W(addr,(u32)s>>16);
  }
}

void line4_r0_s2(u32 mode, u32 reg0)
{
  /* NEGX.L <Ae> */
  if(mode<2)
  {
    s32 s;
    s32 a=reg68.d[reg0]<<0;
    NEGXL(s,a);
    reg68.d[reg0] = (reg68.d[reg0]&0) | (u32)s>>0;
  }
  else
  {
    u32 addr=get_eal[mode](reg0);
    s32 s,a;
    a=read_L(addr)<<0;
    NEGXL(s,a);
    write_L(addr,(u32)s>>0);
  }
}

void line4_r0_s3(u32 mode, u32 reg0)
{
  /* MOVE FROM SR */
  if(mode)
    write_W(get_eaw[mode](reg0),reg68.sr);
  else
    reg68.d[reg0]=(reg68.d[reg0]&0xFFFF0000)+(u16)reg68.sr;
}

void line4_r1_s0(u32 mode, u32 reg0)
{
  /* CLR.B <Ae> */
  if(mode<2)
  {
    s32 s;
    s32 a=0;
    CLRB(s,a);
    reg68.d[reg0] = (reg68.d[reg0]&0xffffff00) | (u32)s>>24;
  }
  else
  {
    u32 addr=get_eab[mode](reg0);
    s32 s,a;
    a=0;
    CLRB(s,a);
    write_B(addr,(u32)s>>24);
  }
}

void line4_r1_s1(u32 mode, u32 reg0)
{
  /* CLR.W <Ae> */
  if(mode<2)
  {
    s32 s;
    s32 a=0;
    CLRW(s,a);
    reg68.d[reg0] = (reg68.d[reg0]&0xffff0000) | (u32)s>>16;
  }
  else
  {
    u32 addr=get_eaw[mode](reg0);
    s32 s,a;
    a=0;
    CLRW(s,a);
    write_W(addr,(u32)s>>16);
  }
}

void line4_r1_s2(u32 mode, u32 reg0)
{
  /* CLR.L <Ae> */
  if(mode<2)
  {
    s32 s;
    s32 a=0;
    CLRL(s,a);
    reg68.d[reg0] = (reg68.d[reg0]&0) | (u32)s>>0;
  }
  else
  {
    u32 addr=get_eal[mode](reg0);
    s32 s,a;
    a=0;
    CLRL(s,a);
    write_L(addr,(u32)s>>0);
  }
}

void line4_r1_s3(u32 mode, u32 reg0)
{
  ILLEGAL;
}

void line4_r2_s0(u32 mode, u32 reg0)
{
  /* NEG.B <Ae> */
  if(mode<2)
  {
    s32 s;
    s32 a=reg68.d[reg0]<<24;
    NEGB(s,a);
    reg68.d[reg0] = (reg68.d[reg0]&0xffffff00) | (u32)s>>24;
  }
  else
  {
    u32 addr=get_eab[mode](reg0);
    s32 s,a;
    a=read_B(addr)<<24;
    NEGB(s,a);
    write_B(addr,(u32)s>>24);
  }
}

void line4_r2_s1(u32 mode, u32 reg0)
{
  /* NEG.W <Ae> */
  if(mode<2)
  {
    s32 s;
    s32 a=reg68.d[reg0]<<16;
    NEGW(s,a);
    reg68.d[reg0] = (reg68.d[reg0]&0xffff0000) | (u32)s>>16;
  }
  else
  {
    u32 addr=get_eaw[mode](reg0);
    s32 s,a;
    a=read_W(addr)<<16;
    NEGW(s,a);
    write_W(addr,(u32)s>>16);
  }
}

void line4_r2_s2(u32 mode, u32 reg0)
{
  /* NEG.L <Ae> */
  if(mode<2)
  {
    s32 s;
    s32 a=reg68.d[reg0]<<0;
    NEGL(s,a);
    reg68.d[reg0] = (reg68.d[reg0]&0) | (u32)s>>0;
  }
  else
  {
    u32 addr=get_eal[mode](reg0);
    s32 s,a;
    a=read_L(addr)<<0;
    NEGL(s,a);
    write_L(addr,(u32)s>>0);
  }
}

void line4_r2_s3(u32 mode, u32 reg0)
{
  /* MOVE TO CCR */
  if(mode)
    SET_CCR(reg68.sr,read_W(get_eaw[mode](reg0)));
  else
    SET_CCR(reg68.sr,reg68.d[reg0]);
}

void line4_r3_s0(u32 mode, u32 reg0)
{
  /* NOT.B <Ae> */
  if(mode<2)
  {
    s32 s;
    s32 a=reg68.d[reg0]<<24;
    NOTB(s,a);
    reg68.d[reg0] = (reg68.d[reg0]&0xffffff00) | (u32)s>>24;
  }
  else
  {
    u32 addr=get_eab[mode](reg0);
    s32 s,a;
    a=read_B(addr)<<24;
    NOTB(s,a);
    write_B(addr,(u32)s>>24);
  }
}

void line4_r3_s1(u32 mode, u32 reg0)
{
  /* NOT.W <Ae> */
  if(mode<2)
  {
    s32 s;
    s32 a=reg68.d[reg0]<<16;
    NOTW(s,a);
    reg68.d[reg0] = (reg68.d[reg0]&0xffff0000) | (u32)s>>16;
  }
  else
  {
    u32 addr=get_eaw[mode](reg0);
    s32 s,a;
    a=read_W(addr)<<16;
    NOTW(s,a);
    write_W(addr,(u32)s>>16);
  }
}

void line4_r3_s2(u32 mode, u32 reg0)
{
  /* NOT.L <Ae> */
  if(mode<2)
  {
    s32 s;
    s32 a=reg68.d[reg0]<<0;
    NOTL(s,a);
    reg68.d[reg0] = (reg68.d[reg0]&0) | (u32)s>>0;
  }
  else
  {
    u32 addr=get_eal[mode](reg0);
    s32 s,a;
    a=read_L(addr)<<0;
    NOTL(s,a);
    write_L(addr,(u32)s>>0);
  }
}

void line4_r3_s3(u32 mode, u32 reg0)
{
  /* MOVE TO SR */
  if(mode)
    reg68.sr = read_W(get_eaw[mode](reg0));
  else
    reg68.sr = (u16)reg68.d[reg0];
}

void line4_r4_s0(u32 mode, u32 reg0)
{
  /* NBCD.B <Ae> */
  if(mode<2)
  {
    s32 s;
    s32 a=reg68.d[reg0]<<24;
    NBCDB(s,a);
    reg68.d[reg0] = (reg68.d[reg0]&0xffffff00) | (u32)s>>24;
  }
  else
  {
    u32 addr=get_eab[mode](reg0);
    s32 s,a;
    a=read_B(addr)<<24;
    NBCDB(s,a);
    write_B(addr,(u32)s>>24);
  }
}

void line4_r4_s1(u32 mode, u32 reg0)
{
  /* SWP or PEA */
  if(!mode){ SWAP(reg68.d[reg0]); }
  else pushl(get_eal[mode](reg0));
}

void line4_r4_s2(u32 mode, u32 reg0)
{
  if(!mode){ EXTW(reg68.d[reg0]); }
  else movemmemw(mode,reg0);
}

void line4_r4_s3(u32 mode, u32 reg0)
{
  if(!mode){ EXTL(reg68.d[reg0]); }
  else movemmeml(mode,reg0);
}

void line4_r5_s0(u32 mode, u32 reg0)
{
  /* TST.B <Ae> */
  if(mode<2)
  {
    s32 s;
    s32 a=reg68.d[reg0]<<24;
    TSTB(s,a);
  }
  else
  {
    u32 addr=get_eab[mode](reg0);
    s32 s,a;
    a=read_B(addr)<<24;
    TSTB(s,a);
  }
}

void line4_r5_s1(u32 mode, u32 reg0)
{
  /* TST.W <Ae> */
  if(mode<2)
  {
    s32 s;
    s32 a=reg68.d[reg0]<<16;
    TSTW(s,a);
  }
  else
  {
    u32 addr=get_eaw[mode](reg0);
    s32 s,a;
    a=read_W(addr)<<16;
    TSTW(s,a);
  }
}

void line4_r5_s2(u32 mode, u32 reg0)
{
  /* TST.L <Ae> */
  if(mode<2)
  {
    s32 s;
    s32 a=reg68.d[reg0]<<0;
    TSTL(s,a);
  }
  else
  {
    u32 addr=get_eal[mode](reg0);
    s32 s,a;
    a=read_L(addr)<<0;
    TSTL(s,a);
  }
}

void line4_r5_s3(u32 mode, u32 reg0)
{
  if(mode<2)
  {
    s32 a = reg68.d[reg0]<<24;
    TAS(a);
    reg68.d[reg0] = (reg68.d[reg0]&0xFFFFFF00) | ((u32)a>>24);
  }
  else
  {
    s32 a;
    if(mode==7 && reg0>1){ ILLEGAL; }
    else
    {
      u32 addr = get_eab[mode](reg0);
      a = read_B(addr)<<24;
      TAS(a);
      write_B(addr,a>>24);
    }
  }
}

void line4_r6_s0(u32 mode, u32 reg0)
{
  ILLEGAL;
}

void line4_r6_s1(u32 mode, u32 reg0)
{
  ILLEGAL;
}

void line4_r6_s2(u32 mode, u32 reg0)
{
  movemregw(mode,reg0);
}

void line4_r6_s3(u32 mode, u32 reg0)
{
  movemregl(mode,reg0);
}

void line4_r7_s0(u32 mode, u32 reg0)
{
  ILLEGAL;
}

void line4_r7_s1(u32 mode, u32 reg0)
{
  (funky4_func[mode])(reg0);
}

void line4_r7_s2(u32 mode, u32 reg0)
{
  /* JSR <Ae> */
  u32 addr = get_eal[mode](reg0);
  pushl(reg68.pc);
  reg68.pc = addr;
  ADDCYCLE(4);
}

void line4_r7_s3(u32 mode, u32 reg0)
{
  /* JMP <Ae> */
  u32 addr = get_eal[mode](reg0);
  reg68.pc = addr;
  ADDCYCLE(4);
}

static void (*line4_0_func[8])(u32,u32) =
{
  line4_r0_s0,line4_r1_s0,line4_r2_s0,line4_r3_s0,line4_r4_s0,line4_r5_s0,line4_r6_s0,line4_r7_s0,
};

static void (*line4_1_func[8])(u32,u32) =
{
  line4_r0_s1,line4_r1_s1,line4_r2_s1,line4_r3_s1,line4_r4_s1,line4_r5_s1,line4_r6_s1,line4_r7_s1,
};

static void (*line4_2_func[8])(u32,u32) =
{
  line4_r0_s2,line4_r1_s2,line4_r2_s2,line4_r3_s2,line4_r4_s2,line4_r5_s2,line4_r6_s2,line4_r7_s2,
};

static void (*line4_3_func[8])(u32,u32) =
{
  line4_r0_s3,line4_r1_s3,line4_r2_s3,line4_r3_s3,line4_r4_s3,line4_r5_s3,line4_r6_s3,line4_r7_s3,
};

void line400(u32 reg9, u32 reg0)
{
  (line4_0_func[reg9])(0,reg0);
}

void line401(u32 reg9, u32 reg0)
{
  (line4_0_func[reg9])(1,reg0);
}

void line402(u32 reg9, u32 reg0)
{
  (line4_0_func[reg9])(2,reg0);
}

void line403(u32 reg9, u32 reg0)
{
  (line4_0_func[reg9])(3,reg0);
}

void line404(u32 reg9, u32 reg0)
{
  (line4_0_func[reg9])(4,reg0);
}

void line405(u32 reg9, u32 reg0)
{
  (line4_0_func[reg9])(5,reg0);
}

void line406(u32 reg9, u32 reg0)
{
  (line4_0_func[reg9])(6,reg0);
}

void line407(u32 reg9, u32 reg0)
{
  (line4_0_func[reg9])(7,reg0);
}

void line408(u32 reg9, u32 reg0)
{
  (line4_1_func[reg9])(0,reg0);
}

void line409(u32 reg9, u32 reg0)
{
  (line4_1_func[reg9])(1,reg0);
}

void line40A(u32 reg9, u32 reg0)
{
  (line4_1_func[reg9])(2,reg0);
}

void line40B(u32 reg9, u32 reg0)
{
  (line4_1_func[reg9])(3,reg0);
}

void line40C(u32 reg9, u32 reg0)
{
  (line4_1_func[reg9])(4,reg0);
}

void line40D(u32 reg9, u32 reg0)
{
  (line4_1_func[reg9])(5,reg0);
}

void line40E(u32 reg9, u32 reg0)
{
  (line4_1_func[reg9])(6,reg0);
}

void line40F(u32 reg9, u32 reg0)
{
  (line4_1_func[reg9])(7,reg0);
}

void line410(u32 reg9, u32 reg0)
{
  (line4_2_func[reg9])(0,reg0);
}

void line411(u32 reg9, u32 reg0)
{
  (line4_2_func[reg9])(1,reg0);
}

void line412(u32 reg9, u32 reg0)
{
  (line4_2_func[reg9])(2,reg0);
}

void line413(u32 reg9, u32 reg0)
{
  (line4_2_func[reg9])(3,reg0);
}

void line414(u32 reg9, u32 reg0)
{
  (line4_2_func[reg9])(4,reg0);
}

void line415(u32 reg9, u32 reg0)
{
  (line4_2_func[reg9])(5,reg0);
}

void line416(u32 reg9, u32 reg0)
{
  (line4_2_func[reg9])(6,reg0);
}

void line417(u32 reg9, u32 reg0)
{
  (line4_2_func[reg9])(7,reg0);
}

void line418(u32 reg9, u32 reg0)
{
  (line4_3_func[reg9])(0,reg0);
}

void line419(u32 reg9, u32 reg0)
{
  (line4_3_func[reg9])(1,reg0);
}

void line41A(u32 reg9, u32 reg0)
{
  (line4_3_func[reg9])(2,reg0);
}

void line41B(u32 reg9, u32 reg0)
{
  (line4_3_func[reg9])(3,reg0);
}

void line41C(u32 reg9, u32 reg0)
{
  (line4_3_func[reg9])(4,reg0);
}

void line41D(u32 reg9, u32 reg0)
{
  (line4_3_func[reg9])(5,reg0);
}

void line41E(u32 reg9, u32 reg0)
{
  (line4_3_func[reg9])(6,reg0);
}

void line41F(u32 reg9, u32 reg0)
{
  (line4_3_func[reg9])(7,reg0);
}

void line420(u32 reg9, u32 reg0)
{
  ILLEGAL;
}

void line421(u32 reg9, u32 reg0)
{
  ILLEGAL;
}

void line422(u32 reg9, u32 reg0)
{
  ILLEGAL;
}

void line423(u32 reg9, u32 reg0)
{
  ILLEGAL;
}

void line424(u32 reg9, u32 reg0)
{
  ILLEGAL;
}

void line425(u32 reg9, u32 reg0)
{
  ILLEGAL;
}

void line426(u32 reg9, u32 reg0)
{
  ILLEGAL;
}

void line427(u32 reg9, u32 reg0)
{
  ILLEGAL;
}

void line428(u32 reg9, u32 reg0)
{
  ILLEGAL;
}

void line429(u32 reg9, u32 reg0)
{
  ILLEGAL;
}

void line42A(u32 reg9, u32 reg0)
{
  ILLEGAL;
}

void line42B(u32 reg9, u32 reg0)
{
  ILLEGAL;
}

void line42C(u32 reg9, u32 reg0)
{
  ILLEGAL;
}

void line42D(u32 reg9, u32 reg0)
{
  ILLEGAL;
}

void line42E(u32 reg9, u32 reg0)
{
  ILLEGAL;
}

void line42F(u32 reg9, u32 reg0)
{
  ILLEGAL;
}

void line430(u32 reg9, u32 reg0)
{
  /* CHK.W Dx,Dy */
  s32 a,b;
  a = reg68.d[reg0]<<16;
  b = reg68.d[reg9]<<16;
  CHKW(a,b);
}

void line431(u32 reg9, u32 reg0)
{
  /* CHK <AE>,Dn */;
  ILLEGAL;
}

void line432(u32 reg9, u32 reg0)
{
  /* CHK.W <Ae>,Dn */
  s32 a,b;
  u32 addr;
  addr = get_eaw[2](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  CHKW(a,b);
}

void line433(u32 reg9, u32 reg0)
{
  /* CHK.W <Ae>,Dn */
  s32 a,b;
  u32 addr;
  addr = get_eaw[3](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  CHKW(a,b);
}

void line434(u32 reg9, u32 reg0)
{
  /* CHK.W <Ae>,Dn */
  s32 a,b;
  u32 addr;
  addr = get_eaw[4](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  CHKW(a,b);
}

void line435(u32 reg9, u32 reg0)
{
  /* CHK.W <Ae>,Dn */
  s32 a,b;
  u32 addr;
  addr = get_eaw[5](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  CHKW(a,b);
}

void line436(u32 reg9, u32 reg0)
{
  /* CHK.W <Ae>,Dn */
  s32 a,b;
  u32 addr;
  addr = get_eaw[6](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  CHKW(a,b);
}

void line437(u32 reg9, u32 reg0)
{
  /* CHK.W <Ae>,Dn */
  s32 a,b;
  u32 addr;
  addr = get_eaw[7](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  CHKW(a,b);
}

void line438(u32 reg9, u32 reg0)
{
  /* LEA <AE>,an */
  ILLEGAL;
}

void line439(u32 reg9, u32 reg0)
{
  /* LEA <AE>,an */
  ILLEGAL;
}

void line43A(u32 reg9, u32 reg0)
{
  /* LEA <AE>,an */
  reg68.a[reg9] = reg68.a[reg0];
}

void line43B(u32 reg9, u32 reg0)
{
  /* LEA <AE>,an */
  ILLEGAL;
}

void line43C(u32 reg9, u32 reg0)
{
  /* LEA <AE>,an */
  ILLEGAL;
}

void line43D(u32 reg9, u32 reg0)
{
  /* LEA <AE>,an */
  reg68.a[reg9] = reg68.a[reg0] + get_nextw();
}

void line43E(u32 reg9, u32 reg0)
{
  /* LEA <AE>,an */
  reg68.a[reg9] = (get_eal[6])(reg0);
}

void line43F(u32 reg9, u32 reg0)
{
  /* LEA <AE>,an */
  reg68.a[reg9] = (get_eal[7])(reg0);
}

void line500(u32 reg9, u32 reg0)
{
  /* ADD.B #imm,Dy */
  s32 a,b,s;
  a = (((reg9-1)&7)+1)<<24;
  b = reg68.d[reg0]<<24;
  ADDB(s,a,b);
  reg68.d[reg0] = (reg68.d[reg0]&0xffffff00) + ((u32)s>>24);
}

void line501(u32 reg9, u32 reg0)
{
  ILLEGAL;
}

void line502(u32 reg9, u32 reg0)
{
  /* ADD.B #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = (((reg9-1)&7)+1)<<24;
  addr = get_eab[2](reg0);
  b = read_B(addr)<<24;
  ADDB(s,a,b);
  write_B(addr,(u32)s>>24);
}

void line503(u32 reg9, u32 reg0)
{
  /* ADD.B #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = (((reg9-1)&7)+1)<<24;
  addr = get_eab[3](reg0);
  b = read_B(addr)<<24;
  ADDB(s,a,b);
  write_B(addr,(u32)s>>24);
}

void line504(u32 reg9, u32 reg0)
{
  /* ADD.B #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = (((reg9-1)&7)+1)<<24;
  addr = get_eab[4](reg0);
  b = read_B(addr)<<24;
  ADDB(s,a,b);
  write_B(addr,(u32)s>>24);
}

void line505(u32 reg9, u32 reg0)
{
  /* ADD.B #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = (((reg9-1)&7)+1)<<24;
  addr = get_eab[5](reg0);
  b = read_B(addr)<<24;
  ADDB(s,a,b);
  write_B(addr,(u32)s>>24);
}

void line506(u32 reg9, u32 reg0)
{
  /* ADD.B #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = (((reg9-1)&7)+1)<<24;
  addr = get_eab[6](reg0);
  b = read_B(addr)<<24;
  ADDB(s,a,b);
  write_B(addr,(u32)s>>24);
}

void line507(u32 reg9, u32 reg0)
{
  /* ADD.B #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = (((reg9-1)&7)+1)<<24;
  addr = get_eab[7](reg0);
  b = read_B(addr)<<24;
  ADDB(s,a,b);
  write_B(addr,(u32)s>>24);
}

void line508(u32 reg9, u32 reg0)
{
  /* ADD.W #imm,Dy */
  s32 a,b,s;
  a = (((reg9-1)&7)+1)<<16;
  b = reg68.d[reg0]<<16;
  ADDW(s,a,b);
  reg68.d[reg0] = (reg68.d[reg0]&0xffff0000) + ((u32)s>>16);
}

void line509(u32 reg9, u32 reg0)
{
  /* ADD.W #imm,Ay */
  s32 a,b,s;
  a = (((reg9-1)&7)+1)<<16;
  b = reg68.a[reg0];
  ADDAW(s,a,b);
  reg68.a[reg0] = s;
}

void line50A(u32 reg9, u32 reg0)
{
  /* ADD.W #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = (((reg9-1)&7)+1)<<16;
  addr = get_eaw[2](reg0);
  b = read_W(addr)<<16;
  ADDW(s,a,b);
  write_W(addr,(u32)s>>16);
}

void line50B(u32 reg9, u32 reg0)
{
  /* ADD.W #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = (((reg9-1)&7)+1)<<16;
  addr = get_eaw[3](reg0);
  b = read_W(addr)<<16;
  ADDW(s,a,b);
  write_W(addr,(u32)s>>16);
}

void line50C(u32 reg9, u32 reg0)
{
  /* ADD.W #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = (((reg9-1)&7)+1)<<16;
  addr = get_eaw[4](reg0);
  b = read_W(addr)<<16;
  ADDW(s,a,b);
  write_W(addr,(u32)s>>16);
}

void line50D(u32 reg9, u32 reg0)
{
  /* ADD.W #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = (((reg9-1)&7)+1)<<16;
  addr = get_eaw[5](reg0);
  b = read_W(addr)<<16;
  ADDW(s,a,b);
  write_W(addr,(u32)s>>16);
}

void line50E(u32 reg9, u32 reg0)
{
  /* ADD.W #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = (((reg9-1)&7)+1)<<16;
  addr = get_eaw[6](reg0);
  b = read_W(addr)<<16;
  ADDW(s,a,b);
  write_W(addr,(u32)s>>16);
}

void line50F(u32 reg9, u32 reg0)
{
  /* ADD.W #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = (((reg9-1)&7)+1)<<16;
  addr = get_eaw[7](reg0);
  b = read_W(addr)<<16;
  ADDW(s,a,b);
  write_W(addr,(u32)s>>16);
}

void line510(u32 reg9, u32 reg0)
{
  /* ADD.L #imm,Dy */
  s32 a,b,s;
  a = (((reg9-1)&7)+1)<<0;
  b = reg68.d[reg0]<<0;
  ADDL(s,a,b);
  reg68.d[reg0] = (reg68.d[reg0]&0) + ((u32)s>>0);
}

void line511(u32 reg9, u32 reg0)
{
  /* ADD.L #imm,Ay */
  s32 a,b,s;
  a = (((reg9-1)&7)+1)<<0;
  b = reg68.a[reg0];
  ADDAL(s,a,b);
  reg68.a[reg0] = s;
}

void line512(u32 reg9, u32 reg0)
{
  /* ADD.L #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = (((reg9-1)&7)+1)<<0;
  addr = get_eal[2](reg0);
  b = read_L(addr)<<0;
  ADDL(s,a,b);
  write_L(addr,(u32)s>>0);
}

void line513(u32 reg9, u32 reg0)
{
  /* ADD.L #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = (((reg9-1)&7)+1)<<0;
  addr = get_eal[3](reg0);
  b = read_L(addr)<<0;
  ADDL(s,a,b);
  write_L(addr,(u32)s>>0);
}

void line514(u32 reg9, u32 reg0)
{
  /* ADD.L #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = (((reg9-1)&7)+1)<<0;
  addr = get_eal[4](reg0);
  b = read_L(addr)<<0;
  ADDL(s,a,b);
  write_L(addr,(u32)s>>0);
}

void line515(u32 reg9, u32 reg0)
{
  /* ADD.L #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = (((reg9-1)&7)+1)<<0;
  addr = get_eal[5](reg0);
  b = read_L(addr)<<0;
  ADDL(s,a,b);
  write_L(addr,(u32)s>>0);
}

void line516(u32 reg9, u32 reg0)
{
  /* ADD.L #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = (((reg9-1)&7)+1)<<0;
  addr = get_eal[6](reg0);
  b = read_L(addr)<<0;
  ADDL(s,a,b);
  write_L(addr,(u32)s>>0);
}

void line517(u32 reg9, u32 reg0)
{
  /* ADD.L #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = (((reg9-1)&7)+1)<<0;
  addr = get_eal[7](reg0);
  b = read_L(addr)<<0;
  ADDL(s,a,b);
  write_L(addr,(u32)s>>0);
}

void line518(u32 reg9, u32 reg0)
{
  /* Scc Dn */
  reg68.d[reg0] = (reg68.d[reg0]&0xFFFFFF00) + (u8)-((is_cc[reg9])()^1);
}

void line519(u32 reg9, u32 reg0)
{
  /* DBcc Dn,<adr> */
  if((is_cc[reg9])())
  {
    s32 a;
    a=reg68.d[reg0]-1;
    a&=0xFFFF;
    reg68.d[reg0] = (reg68.d[reg0]&0xFFFF0000) + a;
    if(a!=0xFFFF)
    {
      u32 pc=reg68.pc;
      reg68.pc = pc+get_nextw();
    }
    else reg68.pc += 2;
  }
  else reg68.pc += 2;
}

void line51A(u32 reg9, u32 reg0)
{
  /* Scc <AE> */
  u32 addr;
  addr = get_eab[2](reg0);
  write_B(addr,-((is_cc[reg9])()^1));
}

void line51B(u32 reg9, u32 reg0)
{
  /* Scc <AE> */
  u32 addr;
  addr = get_eab[3](reg0);
  write_B(addr,-((is_cc[reg9])()^1));
}

void line51C(u32 reg9, u32 reg0)
{
  /* Scc <AE> */
  u32 addr;
  addr = get_eab[4](reg0);
  write_B(addr,-((is_cc[reg9])()^1));
}

void line51D(u32 reg9, u32 reg0)
{
  /* Scc <AE> */
  u32 addr;
  addr = get_eab[5](reg0);
  write_B(addr,-((is_cc[reg9])()^1));
}

void line51E(u32 reg9, u32 reg0)
{
  /* Scc <AE> */
  u32 addr;
  addr = get_eab[6](reg0);
  write_B(addr,-((is_cc[reg9])()^1));
}

void line51F(u32 reg9, u32 reg0)
{
  /* Scc <AE> */
  u32 addr;
  addr = get_eab[7](reg0);
  write_B(addr,-((is_cc[reg9])()^1));
}

void line520(u32 reg9, u32 reg0)
{
  /* SUB.B #imm,Dy */
  s32 a,b,s;
  a = (((reg9-1)&7)+1)<<24;
  b = reg68.d[reg0]<<24;
  SUBB(s,a,b);
  reg68.d[reg0] = (reg68.d[reg0]&0xffffff00) + ((u32)s>>24);
}

void line521(u32 reg9, u32 reg0)
{
  ILLEGAL;
}

void line522(u32 reg9, u32 reg0)
{
  /* SUB.B #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = (((reg9-1)&7)+1)<<24;
  addr = get_eab[2](reg0);
  b = read_B(addr)<<24;
  SUBB(s,a,b);
  write_B(addr,(u32)s>>24);
}

void line523(u32 reg9, u32 reg0)
{
  /* SUB.B #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = (((reg9-1)&7)+1)<<24;
  addr = get_eab[3](reg0);
  b = read_B(addr)<<24;
  SUBB(s,a,b);
  write_B(addr,(u32)s>>24);
}

void line524(u32 reg9, u32 reg0)
{
  /* SUB.B #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = (((reg9-1)&7)+1)<<24;
  addr = get_eab[4](reg0);
  b = read_B(addr)<<24;
  SUBB(s,a,b);
  write_B(addr,(u32)s>>24);
}

void line525(u32 reg9, u32 reg0)
{
  /* SUB.B #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = (((reg9-1)&7)+1)<<24;
  addr = get_eab[5](reg0);
  b = read_B(addr)<<24;
  SUBB(s,a,b);
  write_B(addr,(u32)s>>24);
}

void line526(u32 reg9, u32 reg0)
{
  /* SUB.B #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = (((reg9-1)&7)+1)<<24;
  addr = get_eab[6](reg0);
  b = read_B(addr)<<24;
  SUBB(s,a,b);
  write_B(addr,(u32)s>>24);
}

void line527(u32 reg9, u32 reg0)
{
  /* SUB.B #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = (((reg9-1)&7)+1)<<24;
  addr = get_eab[7](reg0);
  b = read_B(addr)<<24;
  SUBB(s,a,b);
  write_B(addr,(u32)s>>24);
}

void line528(u32 reg9, u32 reg0)
{
  /* SUB.W #imm,Dy */
  s32 a,b,s;
  a = (((reg9-1)&7)+1)<<16;
  b = reg68.d[reg0]<<16;
  SUBW(s,a,b);
  reg68.d[reg0] = (reg68.d[reg0]&0xffff0000) + ((u32)s>>16);
}

void line529(u32 reg9, u32 reg0)
{
  /* SUB.W #imm,Ay */
  s32 a,b,s;
  a = (((reg9-1)&7)+1)<<16;
  b = reg68.a[reg0];
  SUBAW(s,a,b);
  reg68.a[reg0] = s;
}

void line52A(u32 reg9, u32 reg0)
{
  /* SUB.W #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = (((reg9-1)&7)+1)<<16;
  addr = get_eaw[2](reg0);
  b = read_W(addr)<<16;
  SUBW(s,a,b);
  write_W(addr,(u32)s>>16);
}

void line52B(u32 reg9, u32 reg0)
{
  /* SUB.W #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = (((reg9-1)&7)+1)<<16;
  addr = get_eaw[3](reg0);
  b = read_W(addr)<<16;
  SUBW(s,a,b);
  write_W(addr,(u32)s>>16);
}

void line52C(u32 reg9, u32 reg0)
{
  /* SUB.W #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = (((reg9-1)&7)+1)<<16;
  addr = get_eaw[4](reg0);
  b = read_W(addr)<<16;
  SUBW(s,a,b);
  write_W(addr,(u32)s>>16);
}

void line52D(u32 reg9, u32 reg0)
{
  /* SUB.W #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = (((reg9-1)&7)+1)<<16;
  addr = get_eaw[5](reg0);
  b = read_W(addr)<<16;
  SUBW(s,a,b);
  write_W(addr,(u32)s>>16);
}

void line52E(u32 reg9, u32 reg0)
{
  /* SUB.W #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = (((reg9-1)&7)+1)<<16;
  addr = get_eaw[6](reg0);
  b = read_W(addr)<<16;
  SUBW(s,a,b);
  write_W(addr,(u32)s>>16);
}

void line52F(u32 reg9, u32 reg0)
{
  /* SUB.W #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = (((reg9-1)&7)+1)<<16;
  addr = get_eaw[7](reg0);
  b = read_W(addr)<<16;
  SUBW(s,a,b);
  write_W(addr,(u32)s>>16);
}

void line530(u32 reg9, u32 reg0)
{
  /* SUB.L #imm,Dy */
  s32 a,b,s;
  a = (((reg9-1)&7)+1)<<0;
  b = reg68.d[reg0]<<0;
  SUBL(s,a,b);
  reg68.d[reg0] = (reg68.d[reg0]&0) + ((u32)s>>0);
}

void line531(u32 reg9, u32 reg0)
{
  /* SUB.L #imm,Ay */
  s32 a,b,s;
  a = (((reg9-1)&7)+1)<<0;
  b = reg68.a[reg0];
  SUBAL(s,a,b);
  reg68.a[reg0] = s;
}

void line532(u32 reg9, u32 reg0)
{
  /* SUB.L #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = (((reg9-1)&7)+1)<<0;
  addr = get_eal[2](reg0);
  b = read_L(addr)<<0;
  SUBL(s,a,b);
  write_L(addr,(u32)s>>0);
}

void line533(u32 reg9, u32 reg0)
{
  /* SUB.L #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = (((reg9-1)&7)+1)<<0;
  addr = get_eal[3](reg0);
  b = read_L(addr)<<0;
  SUBL(s,a,b);
  write_L(addr,(u32)s>>0);
}

void line534(u32 reg9, u32 reg0)
{
  /* SUB.L #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = (((reg9-1)&7)+1)<<0;
  addr = get_eal[4](reg0);
  b = read_L(addr)<<0;
  SUBL(s,a,b);
  write_L(addr,(u32)s>>0);
}

void line535(u32 reg9, u32 reg0)
{
  /* SUB.L #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = (((reg9-1)&7)+1)<<0;
  addr = get_eal[5](reg0);
  b = read_L(addr)<<0;
  SUBL(s,a,b);
  write_L(addr,(u32)s>>0);
}

void line536(u32 reg9, u32 reg0)
{
  /* SUB.L #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = (((reg9-1)&7)+1)<<0;
  addr = get_eal[6](reg0);
  b = read_L(addr)<<0;
  SUBL(s,a,b);
  write_L(addr,(u32)s>>0);
}

void line537(u32 reg9, u32 reg0)
{
  /* SUB.L #imm,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = (((reg9-1)&7)+1)<<0;
  addr = get_eal[7](reg0);
  b = read_L(addr)<<0;
  SUBL(s,a,b);
  write_L(addr,(u32)s>>0);
}

void line538(u32 reg9, u32 reg0)
{
  /* Scc Dn */
  reg68.d[reg0] = (reg68.d[reg0]&0xFFFFFF00) + (u8)-(is_cc[reg9])();
}

void line539(u32 reg9, u32 reg0)
{
  /* DBcc Dn,<adr> */
  if(!(is_cc[reg9])())
  {
    s32 a;
    a=reg68.d[reg0]-1;
    a&=0xFFFF;
    reg68.d[reg0] = (reg68.d[reg0]&0xFFFF0000) + a;
    if(a!=0xFFFF)
    {
      u32 pc=reg68.pc;
      reg68.pc = pc+get_nextw();
    }
    else reg68.pc += 2;
  }
  else reg68.pc += 2;
}

void line53A(u32 reg9, u32 reg0)
{
  /* Scc <AE> */
  u32 addr;
  addr = get_eab[2](reg0);
  write_B(addr,-(is_cc[reg9])());
}

void line53B(u32 reg9, u32 reg0)
{
  /* Scc <AE> */
  u32 addr;
  addr = get_eab[3](reg0);
  write_B(addr,-(is_cc[reg9])());
}

void line53C(u32 reg9, u32 reg0)
{
  /* Scc <AE> */
  u32 addr;
  addr = get_eab[4](reg0);
  write_B(addr,-(is_cc[reg9])());
}

void line53D(u32 reg9, u32 reg0)
{
  /* Scc <AE> */
  u32 addr;
  addr = get_eab[5](reg0);
  write_B(addr,-(is_cc[reg9])());
}

void line53E(u32 reg9, u32 reg0)
{
  /* Scc <AE> */
  u32 addr;
  addr = get_eab[6](reg0);
  write_B(addr,-(is_cc[reg9])());
}

void line53F(u32 reg9, u32 reg0)
{
  /* Scc <AE> */
  u32 addr;
  addr = get_eab[7](reg0);
  write_B(addr,-(is_cc[reg9])());
}

void line600(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.w */
  if(reg0==0) pc += get_nextw();
  /* Bcc.s */
  else pc += reg0;
  /* Bcc */
  if(!(is_cc[reg9])()) reg68.pc = pc;
}

void line601(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+8;
  /* Bcc */
  if(!(is_cc[reg9])()) reg68.pc = pc;
}

void line602(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+16;
  /* Bcc */
  if(!(is_cc[reg9])()) reg68.pc = pc;
}

void line603(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+24;
  /* Bcc */
  if(!(is_cc[reg9])()) reg68.pc = pc;
}

void line604(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+32;
  /* Bcc */
  if(!(is_cc[reg9])()) reg68.pc = pc;
}

void line605(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+40;
  /* Bcc */
  if(!(is_cc[reg9])()) reg68.pc = pc;
}

void line606(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+48;
  /* Bcc */
  if(!(is_cc[reg9])()) reg68.pc = pc;
}

void line607(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+56;
  /* Bcc */
  if(!(is_cc[reg9])()) reg68.pc = pc;
}

void line608(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+64;
  /* Bcc */
  if(!(is_cc[reg9])()) reg68.pc = pc;
}

void line609(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+72;
  /* Bcc */
  if(!(is_cc[reg9])()) reg68.pc = pc;
}

void line60A(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+80;
  /* Bcc */
  if(!(is_cc[reg9])()) reg68.pc = pc;
}

void line60B(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+88;
  /* Bcc */
  if(!(is_cc[reg9])()) reg68.pc = pc;
}

void line60C(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+96;
  /* Bcc */
  if(!(is_cc[reg9])()) reg68.pc = pc;
}

void line60D(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+104;
  /* Bcc */
  if(!(is_cc[reg9])()) reg68.pc = pc;
}

void line60E(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+112;
  /* Bcc */
  if(!(is_cc[reg9])()) reg68.pc = pc;
}

void line60F(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+120;
  /* Bcc */
  if(!(is_cc[reg9])()) reg68.pc = pc;
}

void line610(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+-128;
  /* Bcc */
  if(!(is_cc[reg9])()) reg68.pc = pc;
}

void line611(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+-120;
  /* Bcc */
  if(!(is_cc[reg9])()) reg68.pc = pc;
}

void line612(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+-112;
  /* Bcc */
  if(!(is_cc[reg9])()) reg68.pc = pc;
}

void line613(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+-104;
  /* Bcc */
  if(!(is_cc[reg9])()) reg68.pc = pc;
}

void line614(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+-96;
  /* Bcc */
  if(!(is_cc[reg9])()) reg68.pc = pc;
}

void line615(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+-88;
  /* Bcc */
  if(!(is_cc[reg9])()) reg68.pc = pc;
}

void line616(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+-80;
  /* Bcc */
  if(!(is_cc[reg9])()) reg68.pc = pc;
}

void line617(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+-72;
  /* Bcc */
  if(!(is_cc[reg9])()) reg68.pc = pc;
}

void line618(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+-64;
  /* Bcc */
  if(!(is_cc[reg9])()) reg68.pc = pc;
}

void line619(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+-56;
  /* Bcc */
  if(!(is_cc[reg9])()) reg68.pc = pc;
}

void line61A(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+-48;
  /* Bcc */
  if(!(is_cc[reg9])()) reg68.pc = pc;
}

void line61B(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+-40;
  /* Bcc */
  if(!(is_cc[reg9])()) reg68.pc = pc;
}

void line61C(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+-32;
  /* Bcc */
  if(!(is_cc[reg9])()) reg68.pc = pc;
}

void line61D(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+-24;
  /* Bcc */
  if(!(is_cc[reg9])()) reg68.pc = pc;
}

void line61E(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+-16;
  /* Bcc */
  if(!(is_cc[reg9])()) reg68.pc = pc;
}

void line61F(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+-8;
  /* Bcc */
  if(!(is_cc[reg9])()) reg68.pc = pc;
}

void line620(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.w */
  if(reg0==0) pc += get_nextw();
  /* Bcc.s */
  else pc += reg0;
  /* BSR */
  if(reg9==0)
  {
    pushl(reg68.pc);
    reg68.pc = pc;
    ADDCYCLE(12);
  }
  else  /* Bcc */
  if((is_cc[reg9])()) reg68.pc = pc;
}

void line621(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+8;
  /* BSR */
  if(reg9==0)
  {
    pushl(reg68.pc);
    reg68.pc = pc;
    ADDCYCLE(12);
  }
  else  /* Bcc */
  if((is_cc[reg9])()) reg68.pc = pc;
}

void line622(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+16;
  /* BSR */
  if(reg9==0)
  {
    pushl(reg68.pc);
    reg68.pc = pc;
    ADDCYCLE(12);
  }
  else  /* Bcc */
  if((is_cc[reg9])()) reg68.pc = pc;
}

void line623(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+24;
  /* BSR */
  if(reg9==0)
  {
    pushl(reg68.pc);
    reg68.pc = pc;
    ADDCYCLE(12);
  }
  else  /* Bcc */
  if((is_cc[reg9])()) reg68.pc = pc;
}

void line624(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+32;
  /* BSR */
  if(reg9==0)
  {
    pushl(reg68.pc);
    reg68.pc = pc;
    ADDCYCLE(12);
  }
  else  /* Bcc */
  if((is_cc[reg9])()) reg68.pc = pc;
}

void line625(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+40;
  /* BSR */
  if(reg9==0)
  {
    pushl(reg68.pc);
    reg68.pc = pc;
    ADDCYCLE(12);
  }
  else  /* Bcc */
  if((is_cc[reg9])()) reg68.pc = pc;
}

void line626(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+48;
  /* BSR */
  if(reg9==0)
  {
    pushl(reg68.pc);
    reg68.pc = pc;
    ADDCYCLE(12);
  }
  else  /* Bcc */
  if((is_cc[reg9])()) reg68.pc = pc;
}

void line627(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+56;
  /* BSR */
  if(reg9==0)
  {
    pushl(reg68.pc);
    reg68.pc = pc;
    ADDCYCLE(12);
  }
  else  /* Bcc */
  if((is_cc[reg9])()) reg68.pc = pc;
}

void line628(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+64;
  /* BSR */
  if(reg9==0)
  {
    pushl(reg68.pc);
    reg68.pc = pc;
    ADDCYCLE(12);
  }
  else  /* Bcc */
  if((is_cc[reg9])()) reg68.pc = pc;
}

void line629(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+72;
  /* BSR */
  if(reg9==0)
  {
    pushl(reg68.pc);
    reg68.pc = pc;
    ADDCYCLE(12);
  }
  else  /* Bcc */
  if((is_cc[reg9])()) reg68.pc = pc;
}

void line62A(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+80;
  /* BSR */
  if(reg9==0)
  {
    pushl(reg68.pc);
    reg68.pc = pc;
    ADDCYCLE(12);
  }
  else  /* Bcc */
  if((is_cc[reg9])()) reg68.pc = pc;
}

void line62B(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+88;
  /* BSR */
  if(reg9==0)
  {
    pushl(reg68.pc);
    reg68.pc = pc;
    ADDCYCLE(12);
  }
  else  /* Bcc */
  if((is_cc[reg9])()) reg68.pc = pc;
}

void line62C(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+96;
  /* BSR */
  if(reg9==0)
  {
    pushl(reg68.pc);
    reg68.pc = pc;
    ADDCYCLE(12);
  }
  else  /* Bcc */
  if((is_cc[reg9])()) reg68.pc = pc;
}

void line62D(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+104;
  /* BSR */
  if(reg9==0)
  {
    pushl(reg68.pc);
    reg68.pc = pc;
    ADDCYCLE(12);
  }
  else  /* Bcc */
  if((is_cc[reg9])()) reg68.pc = pc;
}

void line62E(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+112;
  /* BSR */
  if(reg9==0)
  {
    pushl(reg68.pc);
    reg68.pc = pc;
    ADDCYCLE(12);
  }
  else  /* Bcc */
  if((is_cc[reg9])()) reg68.pc = pc;
}

void line62F(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+120;
  /* BSR */
  if(reg9==0)
  {
    pushl(reg68.pc);
    reg68.pc = pc;
    ADDCYCLE(12);
  }
  else  /* Bcc */
  if((is_cc[reg9])()) reg68.pc = pc;
}

void line630(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+-128;
  /* BSR */
  if(reg9==0)
  {
    pushl(reg68.pc);
    reg68.pc = pc;
    ADDCYCLE(12);
  }
  else  /* Bcc */
  if((is_cc[reg9])()) reg68.pc = pc;
}

void line631(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+-120;
  /* BSR */
  if(reg9==0)
  {
    pushl(reg68.pc);
    reg68.pc = pc;
    ADDCYCLE(12);
  }
  else  /* Bcc */
  if((is_cc[reg9])()) reg68.pc = pc;
}

void line632(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+-112;
  /* BSR */
  if(reg9==0)
  {
    pushl(reg68.pc);
    reg68.pc = pc;
    ADDCYCLE(12);
  }
  else  /* Bcc */
  if((is_cc[reg9])()) reg68.pc = pc;
}

void line633(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+-104;
  /* BSR */
  if(reg9==0)
  {
    pushl(reg68.pc);
    reg68.pc = pc;
    ADDCYCLE(12);
  }
  else  /* Bcc */
  if((is_cc[reg9])()) reg68.pc = pc;
}

void line634(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+-96;
  /* BSR */
  if(reg9==0)
  {
    pushl(reg68.pc);
    reg68.pc = pc;
    ADDCYCLE(12);
  }
  else  /* Bcc */
  if((is_cc[reg9])()) reg68.pc = pc;
}

void line635(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+-88;
  /* BSR */
  if(reg9==0)
  {
    pushl(reg68.pc);
    reg68.pc = pc;
    ADDCYCLE(12);
  }
  else  /* Bcc */
  if((is_cc[reg9])()) reg68.pc = pc;
}

void line636(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+-80;
  /* BSR */
  if(reg9==0)
  {
    pushl(reg68.pc);
    reg68.pc = pc;
    ADDCYCLE(12);
  }
  else  /* Bcc */
  if((is_cc[reg9])()) reg68.pc = pc;
}

void line637(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+-72;
  /* BSR */
  if(reg9==0)
  {
    pushl(reg68.pc);
    reg68.pc = pc;
    ADDCYCLE(12);
  }
  else  /* Bcc */
  if((is_cc[reg9])()) reg68.pc = pc;
}

void line638(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+-64;
  /* BSR */
  if(reg9==0)
  {
    pushl(reg68.pc);
    reg68.pc = pc;
    ADDCYCLE(12);
  }
  else  /* Bcc */
  if((is_cc[reg9])()) reg68.pc = pc;
}

void line639(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+-56;
  /* BSR */
  if(reg9==0)
  {
    pushl(reg68.pc);
    reg68.pc = pc;
    ADDCYCLE(12);
  }
  else  /* Bcc */
  if((is_cc[reg9])()) reg68.pc = pc;
}

void line63A(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+-48;
  /* BSR */
  if(reg9==0)
  {
    pushl(reg68.pc);
    reg68.pc = pc;
    ADDCYCLE(12);
  }
  else  /* Bcc */
  if((is_cc[reg9])()) reg68.pc = pc;
}

void line63B(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+-40;
  /* BSR */
  if(reg9==0)
  {
    pushl(reg68.pc);
    reg68.pc = pc;
    ADDCYCLE(12);
  }
  else  /* Bcc */
  if((is_cc[reg9])()) reg68.pc = pc;
}

void line63C(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+-32;
  /* BSR */
  if(reg9==0)
  {
    pushl(reg68.pc);
    reg68.pc = pc;
    ADDCYCLE(12);
  }
  else  /* Bcc */
  if((is_cc[reg9])()) reg68.pc = pc;
}

void line63D(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+-24;
  /* BSR */
  if(reg9==0)
  {
    pushl(reg68.pc);
    reg68.pc = pc;
    ADDCYCLE(12);
  }
  else  /* Bcc */
  if((is_cc[reg9])()) reg68.pc = pc;
}

void line63E(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+-16;
  /* BSR */
  if(reg9==0)
  {
    pushl(reg68.pc);
    reg68.pc = pc;
    ADDCYCLE(12);
  }
  else  /* Bcc */
  if((is_cc[reg9])()) reg68.pc = pc;
}

void line63F(u32 reg9, u32 reg0)
{
  u32 pc = reg68.pc;
  /* Bcc.s */
  pc += reg0+-8;
  /* BSR */
  if(reg9==0)
  {
    pushl(reg68.pc);
    reg68.pc = pc;
    ADDCYCLE(12);
  }
  else  /* Bcc */
  if((is_cc[reg9])()) reg68.pc = pc;
}

void line700(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((0&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line701(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((1&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line702(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((2&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line703(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((3&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line704(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((4&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line705(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((5&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line706(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((6&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line707(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((7&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line708(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((8&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line709(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((9&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line70A(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((10&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line70B(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((11&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line70C(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((12&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line70D(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((13&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line70E(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((14&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line70F(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((15&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line710(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((16&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line711(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((17&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line712(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((18&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line713(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((19&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line714(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((20&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line715(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((21&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line716(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((22&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line717(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((23&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line718(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((24&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line719(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((25&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line71A(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((26&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line71B(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((27&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line71C(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((28&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line71D(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((29&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line71E(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((30&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line71F(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((31&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line720(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((32&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line721(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((33&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line722(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((34&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line723(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((35&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line724(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((36&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line725(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((37&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line726(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((38&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line727(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((39&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line728(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((40&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line729(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((41&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line72A(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((42&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line72B(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((43&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line72C(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((44&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line72D(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((45&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line72E(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((46&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line72F(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((47&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line730(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((48&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line731(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((49&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line732(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((50&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line733(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((51&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line734(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((52&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line735(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((53&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line736(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((54&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line737(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((55&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line738(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((56&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line739(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((57&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line73A(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((58&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line73B(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((59&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line73C(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((60&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line73D(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((61&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line73E(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((62&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line73F(u32 reg9, u32 reg0)
{
  /* MOVEQ #xx,Dn */
  s32 a=(s32)(s8) (reg0+((63&31)<<3));
  reg68.d[reg9] = a;
  MOVE(a)
}

void line800(u32 reg9, u32 reg0)
{
  /* OR.B Dx,Dy */
  s32 a,b,s;
  a = reg68.d[reg0]<<24;
  b = reg68.d[reg9]<<24;
  ORB(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffffff00) + ((u32)s>>24);
}

void line801(u32 reg9, u32 reg0)
{
  ILLEGAL;
}

void line802(u32 reg9, u32 reg0)
{
  /* OR.B <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eab[2](reg0);
  a = read_B(addr)<<24;
  b = reg68.d[reg9]<<24;
  ORB(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffffff00) + ((u32)s>>24);
}

void line803(u32 reg9, u32 reg0)
{
  /* OR.B <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eab[3](reg0);
  a = read_B(addr)<<24;
  b = reg68.d[reg9]<<24;
  ORB(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffffff00) + ((u32)s>>24);
}

void line804(u32 reg9, u32 reg0)
{
  /* OR.B <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eab[4](reg0);
  a = read_B(addr)<<24;
  b = reg68.d[reg9]<<24;
  ORB(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffffff00) + ((u32)s>>24);
}

void line805(u32 reg9, u32 reg0)
{
  /* OR.B <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eab[5](reg0);
  a = read_B(addr)<<24;
  b = reg68.d[reg9]<<24;
  ORB(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffffff00) + ((u32)s>>24);
}

void line806(u32 reg9, u32 reg0)
{
  /* OR.B <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eab[6](reg0);
  a = read_B(addr)<<24;
  b = reg68.d[reg9]<<24;
  ORB(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffffff00) + ((u32)s>>24);
}

void line807(u32 reg9, u32 reg0)
{
  /* OR.B <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eab[7](reg0);
  a = read_B(addr)<<24;
  b = reg68.d[reg9]<<24;
  ORB(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffffff00) + ((u32)s>>24);
}

void line808(u32 reg9, u32 reg0)
{
  /* OR.W Dx,Dy */
  s32 a,b,s;
  a = reg68.d[reg0]<<16;
  b = reg68.d[reg9]<<16;
  ORW(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffff0000) + ((u32)s>>16);
}

void line809(u32 reg9, u32 reg0)
{
  ILLEGAL;
}

void line80A(u32 reg9, u32 reg0)
{
  /* OR.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[2](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  ORW(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffff0000) + ((u32)s>>16);
}

void line80B(u32 reg9, u32 reg0)
{
  /* OR.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[3](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  ORW(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffff0000) + ((u32)s>>16);
}

void line80C(u32 reg9, u32 reg0)
{
  /* OR.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[4](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  ORW(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffff0000) + ((u32)s>>16);
}

void line80D(u32 reg9, u32 reg0)
{
  /* OR.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[5](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  ORW(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffff0000) + ((u32)s>>16);
}

void line80E(u32 reg9, u32 reg0)
{
  /* OR.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[6](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  ORW(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffff0000) + ((u32)s>>16);
}

void line80F(u32 reg9, u32 reg0)
{
  /* OR.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[7](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  ORW(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffff0000) + ((u32)s>>16);
}

void line810(u32 reg9, u32 reg0)
{
  /* OR.L Dx,Dy */
  s32 a,b,s;
  a = reg68.d[reg0]<<0;
  b = reg68.d[reg9]<<0;
  ORL(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0) + ((u32)s>>0);
}

void line811(u32 reg9, u32 reg0)
{
  ILLEGAL;
}

void line812(u32 reg9, u32 reg0)
{
  /* OR.L <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eal[2](reg0);
  a = read_L(addr)<<0;
  b = reg68.d[reg9]<<0;
  ORL(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0) + ((u32)s>>0);
}

void line813(u32 reg9, u32 reg0)
{
  /* OR.L <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eal[3](reg0);
  a = read_L(addr)<<0;
  b = reg68.d[reg9]<<0;
  ORL(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0) + ((u32)s>>0);
}

void line814(u32 reg9, u32 reg0)
{
  /* OR.L <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eal[4](reg0);
  a = read_L(addr)<<0;
  b = reg68.d[reg9]<<0;
  ORL(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0) + ((u32)s>>0);
}

void line815(u32 reg9, u32 reg0)
{
  /* OR.L <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eal[5](reg0);
  a = read_L(addr)<<0;
  b = reg68.d[reg9]<<0;
  ORL(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0) + ((u32)s>>0);
}

void line816(u32 reg9, u32 reg0)
{
  /* OR.L <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eal[6](reg0);
  a = read_L(addr)<<0;
  b = reg68.d[reg9]<<0;
  ORL(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0) + ((u32)s>>0);
}

void line817(u32 reg9, u32 reg0)
{
  /* OR.L <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eal[7](reg0);
  a = read_L(addr)<<0;
  b = reg68.d[reg9]<<0;
  ORL(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0) + ((u32)s>>0);
}

void line818(u32 reg9, u32 reg0)
{
  /* DIVU.W Dx,Dy */
  s32 a,b,s;
  a = reg68.d[reg0]<<16;
  b = reg68.d[reg9]<<0;
  DIVUW(s,a,b);
  reg68.d[reg9] = s;
}

void line819(u32 reg9, u32 reg0)
{
  /* DIVU.W Ax,Dy */
  s32 a,b,s;
  a = reg68.a[reg0]<<16;
  b = reg68.d[reg9]<<0;
  DIVUW(s,a,b);
  reg68.d[reg9] = s;
}

void line81A(u32 reg9, u32 reg0)
{
  /* DIVU.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[2](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<0;
  DIVUW(s,a,b);
  reg68.d[reg9] = s;
}

void line81B(u32 reg9, u32 reg0)
{
  /* DIVU.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[3](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<0;
  DIVUW(s,a,b);
  reg68.d[reg9] = s;
}

void line81C(u32 reg9, u32 reg0)
{
  /* DIVU.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[4](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<0;
  DIVUW(s,a,b);
  reg68.d[reg9] = s;
}

void line81D(u32 reg9, u32 reg0)
{
  /* DIVU.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[5](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<0;
  DIVUW(s,a,b);
  reg68.d[reg9] = s;
}

void line81E(u32 reg9, u32 reg0)
{
  /* DIVU.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[6](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<0;
  DIVUW(s,a,b);
  reg68.d[reg9] = s;
}

void line81F(u32 reg9, u32 reg0)
{
  /* DIVU.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[7](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<0;
  DIVUW(s,a,b);
  reg68.d[reg9] = s;
}

void line820(u32 reg9, u32 reg0)
{
  /* SBCD Dy,Dx */
  reg0=reg0; reg9=reg9;
}

void line821(u32 reg9, u32 reg0)
{
  /* SBCD -(Ay),-(Ax) */
  reg68.a[reg0] -= 2;
  reg68.a[reg9] -= 2;
}

void line822(u32 reg9, u32 reg0)
{
  /* OR.B Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<24;
  addr = get_eab[2](reg0);
  b = read_B(addr)<<24;
  ORB(s,a,b);
  write_B(addr,(u32)s>>24);
}

void line823(u32 reg9, u32 reg0)
{
  /* OR.B Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<24;
  addr = get_eab[3](reg0);
  b = read_B(addr)<<24;
  ORB(s,a,b);
  write_B(addr,(u32)s>>24);
}

void line824(u32 reg9, u32 reg0)
{
  /* OR.B Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<24;
  addr = get_eab[4](reg0);
  b = read_B(addr)<<24;
  ORB(s,a,b);
  write_B(addr,(u32)s>>24);
}

void line825(u32 reg9, u32 reg0)
{
  /* OR.B Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<24;
  addr = get_eab[5](reg0);
  b = read_B(addr)<<24;
  ORB(s,a,b);
  write_B(addr,(u32)s>>24);
}

void line826(u32 reg9, u32 reg0)
{
  /* OR.B Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<24;
  addr = get_eab[6](reg0);
  b = read_B(addr)<<24;
  ORB(s,a,b);
  write_B(addr,(u32)s>>24);
}

void line827(u32 reg9, u32 reg0)
{
  /* OR.B Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<24;
  addr = get_eab[7](reg0);
  b = read_B(addr)<<24;
  ORB(s,a,b);
  write_B(addr,(u32)s>>24);
}

void line828(u32 reg9, u32 reg0)
{
  /* OR.W Dx,Dy */
  s32 a,b,s;
  a = reg68.d[reg9]<<16;
  b = reg68.d[reg0]<<16;
  ORW(s,a,b);
  reg68.d[reg0] = (reg68.d[reg0]&0xffff0000) + ((u32)s>>16);
}

void line829(u32 reg9, u32 reg0)
{
  ILLEGAL;
}

void line82A(u32 reg9, u32 reg0)
{
  /* OR.W Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<16;
  addr = get_eaw[2](reg0);
  b = read_W(addr)<<16;
  ORW(s,a,b);
  write_W(addr,(u32)s>>16);
}

void line82B(u32 reg9, u32 reg0)
{
  /* OR.W Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<16;
  addr = get_eaw[3](reg0);
  b = read_W(addr)<<16;
  ORW(s,a,b);
  write_W(addr,(u32)s>>16);
}

void line82C(u32 reg9, u32 reg0)
{
  /* OR.W Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<16;
  addr = get_eaw[4](reg0);
  b = read_W(addr)<<16;
  ORW(s,a,b);
  write_W(addr,(u32)s>>16);
}

void line82D(u32 reg9, u32 reg0)
{
  /* OR.W Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<16;
  addr = get_eaw[5](reg0);
  b = read_W(addr)<<16;
  ORW(s,a,b);
  write_W(addr,(u32)s>>16);
}

void line82E(u32 reg9, u32 reg0)
{
  /* OR.W Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<16;
  addr = get_eaw[6](reg0);
  b = read_W(addr)<<16;
  ORW(s,a,b);
  write_W(addr,(u32)s>>16);
}

void line82F(u32 reg9, u32 reg0)
{
  /* OR.W Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<16;
  addr = get_eaw[7](reg0);
  b = read_W(addr)<<16;
  ORW(s,a,b);
  write_W(addr,(u32)s>>16);
}

void line830(u32 reg9, u32 reg0)
{
  /* OR.L Dx,Dy */
  s32 a,b,s;
  a = reg68.d[reg9]<<0;
  b = reg68.d[reg0]<<0;
  ORL(s,a,b);
  reg68.d[reg0] = (reg68.d[reg0]&0) + ((u32)s>>0);
}

void line831(u32 reg9, u32 reg0)
{
  ILLEGAL;
}

void line832(u32 reg9, u32 reg0)
{
  /* OR.L Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<0;
  addr = get_eal[2](reg0);
  b = read_L(addr)<<0;
  ORL(s,a,b);
  write_L(addr,(u32)s>>0);
}

void line833(u32 reg9, u32 reg0)
{
  /* OR.L Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<0;
  addr = get_eal[3](reg0);
  b = read_L(addr)<<0;
  ORL(s,a,b);
  write_L(addr,(u32)s>>0);
}

void line834(u32 reg9, u32 reg0)
{
  /* OR.L Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<0;
  addr = get_eal[4](reg0);
  b = read_L(addr)<<0;
  ORL(s,a,b);
  write_L(addr,(u32)s>>0);
}

void line835(u32 reg9, u32 reg0)
{
  /* OR.L Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<0;
  addr = get_eal[5](reg0);
  b = read_L(addr)<<0;
  ORL(s,a,b);
  write_L(addr,(u32)s>>0);
}

void line836(u32 reg9, u32 reg0)
{
  /* OR.L Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<0;
  addr = get_eal[6](reg0);
  b = read_L(addr)<<0;
  ORL(s,a,b);
  write_L(addr,(u32)s>>0);
}

void line837(u32 reg9, u32 reg0)
{
  /* OR.L Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<0;
  addr = get_eal[7](reg0);
  b = read_L(addr)<<0;
  ORL(s,a,b);
  write_L(addr,(u32)s>>0);
}

void line838(u32 reg9, u32 reg0)
{
  /* DIVS.W Dx,Dy */
  s32 a,b,s;
  a = reg68.d[reg0]<<16;
  b = reg68.d[reg9]<<0;
  DIVSW(s,a,b);
  reg68.d[reg9] = s;
}

void line839(u32 reg9, u32 reg0)
{
  /* DIVS.W Ax,Dy */
  s32 a,b,s;
  a = reg68.a[reg0]<<16;
  b = reg68.d[reg9]<<0;
  DIVSW(s,a,b);
  reg68.d[reg9] = s;
}

void line83A(u32 reg9, u32 reg0)
{
  /* DIVS.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[2](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<0;
  DIVSW(s,a,b);
  reg68.d[reg9] = s;
}

void line83B(u32 reg9, u32 reg0)
{
  /* DIVS.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[3](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<0;
  DIVSW(s,a,b);
  reg68.d[reg9] = s;
}

void line83C(u32 reg9, u32 reg0)
{
  /* DIVS.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[4](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<0;
  DIVSW(s,a,b);
  reg68.d[reg9] = s;
}

void line83D(u32 reg9, u32 reg0)
{
  /* DIVS.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[5](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<0;
  DIVSW(s,a,b);
  reg68.d[reg9] = s;
}

void line83E(u32 reg9, u32 reg0)
{
  /* DIVS.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[6](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<0;
  DIVSW(s,a,b);
  reg68.d[reg9] = s;
}

void line83F(u32 reg9, u32 reg0)
{
  /* DIVS.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[7](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<0;
  DIVSW(s,a,b);
  reg68.d[reg9] = s;
}

void line900(u32 reg9, u32 reg0)
{
  /* SUB.B Dx,Dy */
  s32 a,b,s;
  a = reg68.d[reg0]<<24;
  b = reg68.d[reg9]<<24;
  SUBB(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffffff00) + ((u32)s>>24);
}

void line901(u32 reg9, u32 reg0)
{
  /* SUB.B Ax,Dy */
  s32 a,b,s;
  a = reg68.a[reg0]<<24;
  b = reg68.d[reg9]<<24;
  SUBB(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffffff00) + ((u32)s>>24);
}

void line902(u32 reg9, u32 reg0)
{
  /* SUB.B <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eab[2](reg0);
  a = read_B(addr)<<24;
  b = reg68.d[reg9]<<24;
  SUBB(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffffff00) + ((u32)s>>24);
}

void line903(u32 reg9, u32 reg0)
{
  /* SUB.B <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eab[3](reg0);
  a = read_B(addr)<<24;
  b = reg68.d[reg9]<<24;
  SUBB(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffffff00) + ((u32)s>>24);
}

void line904(u32 reg9, u32 reg0)
{
  /* SUB.B <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eab[4](reg0);
  a = read_B(addr)<<24;
  b = reg68.d[reg9]<<24;
  SUBB(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffffff00) + ((u32)s>>24);
}

void line905(u32 reg9, u32 reg0)
{
  /* SUB.B <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eab[5](reg0);
  a = read_B(addr)<<24;
  b = reg68.d[reg9]<<24;
  SUBB(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffffff00) + ((u32)s>>24);
}

void line906(u32 reg9, u32 reg0)
{
  /* SUB.B <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eab[6](reg0);
  a = read_B(addr)<<24;
  b = reg68.d[reg9]<<24;
  SUBB(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffffff00) + ((u32)s>>24);
}

void line907(u32 reg9, u32 reg0)
{
  /* SUB.B <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eab[7](reg0);
  a = read_B(addr)<<24;
  b = reg68.d[reg9]<<24;
  SUBB(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffffff00) + ((u32)s>>24);
}

void line908(u32 reg9, u32 reg0)
{
  /* SUB.W Dx,Dy */
  s32 a,b,s;
  a = reg68.d[reg0]<<16;
  b = reg68.d[reg9]<<16;
  SUBW(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffff0000) + ((u32)s>>16);
}

void line909(u32 reg9, u32 reg0)
{
  /* SUB.W Ax,Dy */
  s32 a,b,s;
  a = reg68.a[reg0]<<16;
  b = reg68.d[reg9]<<16;
  SUBW(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffff0000) + ((u32)s>>16);
}

void line90A(u32 reg9, u32 reg0)
{
  /* SUB.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[2](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  SUBW(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffff0000) + ((u32)s>>16);
}

void line90B(u32 reg9, u32 reg0)
{
  /* SUB.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[3](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  SUBW(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffff0000) + ((u32)s>>16);
}

void line90C(u32 reg9, u32 reg0)
{
  /* SUB.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[4](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  SUBW(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffff0000) + ((u32)s>>16);
}

void line90D(u32 reg9, u32 reg0)
{
  /* SUB.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[5](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  SUBW(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffff0000) + ((u32)s>>16);
}

void line90E(u32 reg9, u32 reg0)
{
  /* SUB.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[6](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  SUBW(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffff0000) + ((u32)s>>16);
}

void line90F(u32 reg9, u32 reg0)
{
  /* SUB.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[7](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  SUBW(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffff0000) + ((u32)s>>16);
}

void line910(u32 reg9, u32 reg0)
{
  /* SUB.L Dx,Dy */
  s32 a,b,s;
  a = reg68.d[reg0]<<0;
  b = reg68.d[reg9]<<0;
  SUBL(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0) + ((u32)s>>0);
}

void line911(u32 reg9, u32 reg0)
{
  /* SUB.L Ax,Dy */
  s32 a,b,s;
  a = reg68.a[reg0]<<0;
  b = reg68.d[reg9]<<0;
  SUBL(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0) + ((u32)s>>0);
}

void line912(u32 reg9, u32 reg0)
{
  /* SUB.L <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eal[2](reg0);
  a = read_L(addr)<<0;
  b = reg68.d[reg9]<<0;
  SUBL(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0) + ((u32)s>>0);
}

void line913(u32 reg9, u32 reg0)
{
  /* SUB.L <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eal[3](reg0);
  a = read_L(addr)<<0;
  b = reg68.d[reg9]<<0;
  SUBL(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0) + ((u32)s>>0);
}

void line914(u32 reg9, u32 reg0)
{
  /* SUB.L <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eal[4](reg0);
  a = read_L(addr)<<0;
  b = reg68.d[reg9]<<0;
  SUBL(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0) + ((u32)s>>0);
}

void line915(u32 reg9, u32 reg0)
{
  /* SUB.L <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eal[5](reg0);
  a = read_L(addr)<<0;
  b = reg68.d[reg9]<<0;
  SUBL(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0) + ((u32)s>>0);
}

void line916(u32 reg9, u32 reg0)
{
  /* SUB.L <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eal[6](reg0);
  a = read_L(addr)<<0;
  b = reg68.d[reg9]<<0;
  SUBL(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0) + ((u32)s>>0);
}

void line917(u32 reg9, u32 reg0)
{
  /* SUB.L <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eal[7](reg0);
  a = read_L(addr)<<0;
  b = reg68.d[reg9]<<0;
  SUBL(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0) + ((u32)s>>0);
}

void line918(u32 reg9, u32 reg0)
{
  /* SUB.W Dx,Ay */
  s32 a,b,s;
  a = reg68.d[reg0]<<16;
  b = reg68.a[reg9];
  SUBAW(s,a,b);
  reg68.a[reg9] = s;
}

void line919(u32 reg9, u32 reg0)
{
  /* SUB.W Ax,Ay */
  s32 a,b,s;
  a = reg68.a[reg0]<<16;
  b = reg68.a[reg9];
  SUBAW(s,a,b);
  reg68.a[reg9] = s;
}

void line91A(u32 reg9, u32 reg0)
{
  /* SUB.W <Ae>,An */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[2](reg0);
  a = read_W(addr)<<16;
  b = reg68.a[reg9];
  SUBAW(s,a,b);
  reg68.a[reg9] = s;
}

void line91B(u32 reg9, u32 reg0)
{
  /* SUB.W <Ae>,An */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[3](reg0);
  a = read_W(addr)<<16;
  b = reg68.a[reg9];
  SUBAW(s,a,b);
  reg68.a[reg9] = s;
}

void line91C(u32 reg9, u32 reg0)
{
  /* SUB.W <Ae>,An */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[4](reg0);
  a = read_W(addr)<<16;
  b = reg68.a[reg9];
  SUBAW(s,a,b);
  reg68.a[reg9] = s;
}

void line91D(u32 reg9, u32 reg0)
{
  /* SUB.W <Ae>,An */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[5](reg0);
  a = read_W(addr)<<16;
  b = reg68.a[reg9];
  SUBAW(s,a,b);
  reg68.a[reg9] = s;
}

void line91E(u32 reg9, u32 reg0)
{
  /* SUB.W <Ae>,An */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[6](reg0);
  a = read_W(addr)<<16;
  b = reg68.a[reg9];
  SUBAW(s,a,b);
  reg68.a[reg9] = s;
}

void line91F(u32 reg9, u32 reg0)
{
  /* SUB.W <Ae>,An */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[7](reg0);
  a = read_W(addr)<<16;
  b = reg68.a[reg9];
  SUBAW(s,a,b);
  reg68.a[reg9] = s;
}

void line920(u32 reg9, u32 reg0)
{
  s32 a,b,s;
  a = reg68.d[reg0]<<24;
  b = reg68.d[reg9]<<24;
  SUBXB(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffffff00) + ((u32)s>>24);
}

void line921(u32 reg9, u32 reg0)
{
  s32 a,b,s;
  a = read_B(reg68.a[reg0]-=1)<<24;
  b = read_B(reg68.a[reg9]-=1)<<24;
  SUBXB(s,a,b);
  write_B(reg68.a[reg9],(u32)s>>24);
}

void line922(u32 reg9, u32 reg0)
{
  /* SUB.B Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<24;
  addr = get_eab[2](reg0);
  b = read_B(addr)<<24;
  SUBB(s,a,b);
  write_B(addr,(u32)s>>24);
}

void line923(u32 reg9, u32 reg0)
{
  /* SUB.B Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<24;
  addr = get_eab[3](reg0);
  b = read_B(addr)<<24;
  SUBB(s,a,b);
  write_B(addr,(u32)s>>24);
}

void line924(u32 reg9, u32 reg0)
{
  /* SUB.B Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<24;
  addr = get_eab[4](reg0);
  b = read_B(addr)<<24;
  SUBB(s,a,b);
  write_B(addr,(u32)s>>24);
}

void line925(u32 reg9, u32 reg0)
{
  /* SUB.B Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<24;
  addr = get_eab[5](reg0);
  b = read_B(addr)<<24;
  SUBB(s,a,b);
  write_B(addr,(u32)s>>24);
}

void line926(u32 reg9, u32 reg0)
{
  /* SUB.B Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<24;
  addr = get_eab[6](reg0);
  b = read_B(addr)<<24;
  SUBB(s,a,b);
  write_B(addr,(u32)s>>24);
}

void line927(u32 reg9, u32 reg0)
{
  /* SUB.B Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<24;
  addr = get_eab[7](reg0);
  b = read_B(addr)<<24;
  SUBB(s,a,b);
  write_B(addr,(u32)s>>24);
}

void line928(u32 reg9, u32 reg0)
{
  s32 a,b,s;
  a = reg68.d[reg0]<<16;
  b = reg68.d[reg9]<<16;
  SUBXW(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffff0000) + ((u32)s>>16);
}

void line929(u32 reg9, u32 reg0)
{
  s32 a,b,s;
  a = read_W(reg68.a[reg0]-=2)<<16;
  b = read_W(reg68.a[reg9]-=2)<<16;
  SUBXW(s,a,b);
  write_W(reg68.a[reg9],(u32)s>>16);
}

void line92A(u32 reg9, u32 reg0)
{
  /* SUB.W Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<16;
  addr = get_eaw[2](reg0);
  b = read_W(addr)<<16;
  SUBW(s,a,b);
  write_W(addr,(u32)s>>16);
}

void line92B(u32 reg9, u32 reg0)
{
  /* SUB.W Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<16;
  addr = get_eaw[3](reg0);
  b = read_W(addr)<<16;
  SUBW(s,a,b);
  write_W(addr,(u32)s>>16);
}

void line92C(u32 reg9, u32 reg0)
{
  /* SUB.W Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<16;
  addr = get_eaw[4](reg0);
  b = read_W(addr)<<16;
  SUBW(s,a,b);
  write_W(addr,(u32)s>>16);
}

void line92D(u32 reg9, u32 reg0)
{
  /* SUB.W Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<16;
  addr = get_eaw[5](reg0);
  b = read_W(addr)<<16;
  SUBW(s,a,b);
  write_W(addr,(u32)s>>16);
}

void line92E(u32 reg9, u32 reg0)
{
  /* SUB.W Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<16;
  addr = get_eaw[6](reg0);
  b = read_W(addr)<<16;
  SUBW(s,a,b);
  write_W(addr,(u32)s>>16);
}

void line92F(u32 reg9, u32 reg0)
{
  /* SUB.W Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<16;
  addr = get_eaw[7](reg0);
  b = read_W(addr)<<16;
  SUBW(s,a,b);
  write_W(addr,(u32)s>>16);
}

void line930(u32 reg9, u32 reg0)
{
  s32 a,b,s;
  a = reg68.d[reg0]<<0;
  b = reg68.d[reg9]<<0;
  SUBXL(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0) + ((u32)s>>0);
}

void line931(u32 reg9, u32 reg0)
{
  s32 a,b,s;
  a = read_L(reg68.a[reg0]-=4)<<0;
  b = read_L(reg68.a[reg9]-=4)<<0;
  SUBXL(s,a,b);
  write_L(reg68.a[reg9],(u32)s>>0);
}

void line932(u32 reg9, u32 reg0)
{
  /* SUB.L Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<0;
  addr = get_eal[2](reg0);
  b = read_L(addr)<<0;
  SUBL(s,a,b);
  write_L(addr,(u32)s>>0);
}

void line933(u32 reg9, u32 reg0)
{
  /* SUB.L Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<0;
  addr = get_eal[3](reg0);
  b = read_L(addr)<<0;
  SUBL(s,a,b);
  write_L(addr,(u32)s>>0);
}

void line934(u32 reg9, u32 reg0)
{
  /* SUB.L Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<0;
  addr = get_eal[4](reg0);
  b = read_L(addr)<<0;
  SUBL(s,a,b);
  write_L(addr,(u32)s>>0);
}

void line935(u32 reg9, u32 reg0)
{
  /* SUB.L Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<0;
  addr = get_eal[5](reg0);
  b = read_L(addr)<<0;
  SUBL(s,a,b);
  write_L(addr,(u32)s>>0);
}

void line936(u32 reg9, u32 reg0)
{
  /* SUB.L Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<0;
  addr = get_eal[6](reg0);
  b = read_L(addr)<<0;
  SUBL(s,a,b);
  write_L(addr,(u32)s>>0);
}

void line937(u32 reg9, u32 reg0)
{
  /* SUB.L Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<0;
  addr = get_eal[7](reg0);
  b = read_L(addr)<<0;
  SUBL(s,a,b);
  write_L(addr,(u32)s>>0);
}

void line938(u32 reg9, u32 reg0)
{
  /* SUB.L Dx,Ay */
  s32 a,b,s;
  a = reg68.d[reg0]<<0;
  b = reg68.a[reg9];
  SUBAL(s,a,b);
  reg68.a[reg9] = s;
}

void line939(u32 reg9, u32 reg0)
{
  /* SUB.L Ax,Ay */
  s32 a,b,s;
  a = reg68.a[reg0]<<0;
  b = reg68.a[reg9];
  SUBAL(s,a,b);
  reg68.a[reg9] = s;
}

void line93A(u32 reg9, u32 reg0)
{
  /* SUB.L <Ae>,An */
  s32 a,b,s;
  u32 addr;
  addr = get_eal[2](reg0);
  a = read_L(addr)<<0;
  b = reg68.a[reg9];
  SUBAL(s,a,b);
  reg68.a[reg9] = s;
}

void line93B(u32 reg9, u32 reg0)
{
  /* SUB.L <Ae>,An */
  s32 a,b,s;
  u32 addr;
  addr = get_eal[3](reg0);
  a = read_L(addr)<<0;
  b = reg68.a[reg9];
  SUBAL(s,a,b);
  reg68.a[reg9] = s;
}

void line93C(u32 reg9, u32 reg0)
{
  /* SUB.L <Ae>,An */
  s32 a,b,s;
  u32 addr;
  addr = get_eal[4](reg0);
  a = read_L(addr)<<0;
  b = reg68.a[reg9];
  SUBAL(s,a,b);
  reg68.a[reg9] = s;
}

void line93D(u32 reg9, u32 reg0)
{
  /* SUB.L <Ae>,An */
  s32 a,b,s;
  u32 addr;
  addr = get_eal[5](reg0);
  a = read_L(addr)<<0;
  b = reg68.a[reg9];
  SUBAL(s,a,b);
  reg68.a[reg9] = s;
}

void line93E(u32 reg9, u32 reg0)
{
  /* SUB.L <Ae>,An */
  s32 a,b,s;
  u32 addr;
  addr = get_eal[6](reg0);
  a = read_L(addr)<<0;
  b = reg68.a[reg9];
  SUBAL(s,a,b);
  reg68.a[reg9] = s;
}

void line93F(u32 reg9, u32 reg0)
{
  /* SUB.L <Ae>,An */
  s32 a,b,s;
  u32 addr;
  addr = get_eal[7](reg0);
  a = read_L(addr)<<0;
  b = reg68.a[reg9];
  SUBAL(s,a,b);
  reg68.a[reg9] = s;
}

void lineA00(u32 reg9, u32 reg0)
{
  LINEA;
}

void lineB00(u32 reg9, u32 reg0)
{
  /* CMP.B Dx,Dy */
  s32 a,b;
  a = reg68.d[reg0]<<24;
  b = reg68.d[reg9]<<24;
  CMPB(a,b);
}

void lineB01(u32 reg9, u32 reg0)
{
  /* CMP.B Ax,Dy */
  s32 a,b;
  a = reg68.a[reg0]<<24;
  b = reg68.d[reg9]<<24;
  CMPB(a,b);
}

void lineB02(u32 reg9, u32 reg0)
{
  /* CMP.B <Ae>,Dn */
  s32 a,b;
  u32 addr;
  addr = get_eab[2](reg0);
  a = read_B(addr)<<24;
  b = reg68.d[reg9]<<24;
  CMPB(a,b);
}

void lineB03(u32 reg9, u32 reg0)
{
  /* CMP.B <Ae>,Dn */
  s32 a,b;
  u32 addr;
  addr = get_eab[3](reg0);
  a = read_B(addr)<<24;
  b = reg68.d[reg9]<<24;
  CMPB(a,b);
}

void lineB04(u32 reg9, u32 reg0)
{
  /* CMP.B <Ae>,Dn */
  s32 a,b;
  u32 addr;
  addr = get_eab[4](reg0);
  a = read_B(addr)<<24;
  b = reg68.d[reg9]<<24;
  CMPB(a,b);
}

void lineB05(u32 reg9, u32 reg0)
{
  /* CMP.B <Ae>,Dn */
  s32 a,b;
  u32 addr;
  addr = get_eab[5](reg0);
  a = read_B(addr)<<24;
  b = reg68.d[reg9]<<24;
  CMPB(a,b);
}

void lineB06(u32 reg9, u32 reg0)
{
  /* CMP.B <Ae>,Dn */
  s32 a,b;
  u32 addr;
  addr = get_eab[6](reg0);
  a = read_B(addr)<<24;
  b = reg68.d[reg9]<<24;
  CMPB(a,b);
}

void lineB07(u32 reg9, u32 reg0)
{
  /* CMP.B <Ae>,Dn */
  s32 a,b;
  u32 addr;
  addr = get_eab[7](reg0);
  a = read_B(addr)<<24;
  b = reg68.d[reg9]<<24;
  CMPB(a,b);
}

void lineB08(u32 reg9, u32 reg0)
{
  /* CMP.W Dx,Dy */
  s32 a,b;
  a = reg68.d[reg0]<<16;
  b = reg68.d[reg9]<<16;
  CMPW(a,b);
}

void lineB09(u32 reg9, u32 reg0)
{
  /* CMP.W Ax,Dy */
  s32 a,b;
  a = reg68.a[reg0]<<16;
  b = reg68.d[reg9]<<16;
  CMPW(a,b);
}

void lineB0A(u32 reg9, u32 reg0)
{
  /* CMP.W <Ae>,Dn */
  s32 a,b;
  u32 addr;
  addr = get_eaw[2](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  CMPW(a,b);
}

void lineB0B(u32 reg9, u32 reg0)
{
  /* CMP.W <Ae>,Dn */
  s32 a,b;
  u32 addr;
  addr = get_eaw[3](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  CMPW(a,b);
}

void lineB0C(u32 reg9, u32 reg0)
{
  /* CMP.W <Ae>,Dn */
  s32 a,b;
  u32 addr;
  addr = get_eaw[4](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  CMPW(a,b);
}

void lineB0D(u32 reg9, u32 reg0)
{
  /* CMP.W <Ae>,Dn */
  s32 a,b;
  u32 addr;
  addr = get_eaw[5](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  CMPW(a,b);
}

void lineB0E(u32 reg9, u32 reg0)
{
  /* CMP.W <Ae>,Dn */
  s32 a,b;
  u32 addr;
  addr = get_eaw[6](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  CMPW(a,b);
}

void lineB0F(u32 reg9, u32 reg0)
{
  /* CMP.W <Ae>,Dn */
  s32 a,b;
  u32 addr;
  addr = get_eaw[7](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  CMPW(a,b);
}

void lineB10(u32 reg9, u32 reg0)
{
  /* CMP.L Dx,Dy */
  s32 a,b;
  a = reg68.d[reg0]<<0;
  b = reg68.d[reg9]<<0;
  CMPL(a,b);
}

void lineB11(u32 reg9, u32 reg0)
{
  /* CMP.L Ax,Dy */
  s32 a,b;
  a = reg68.a[reg0]<<0;
  b = reg68.d[reg9]<<0;
  CMPL(a,b);
}

void lineB12(u32 reg9, u32 reg0)
{
  /* CMP.L <Ae>,Dn */
  s32 a,b;
  u32 addr;
  addr = get_eal[2](reg0);
  a = read_L(addr)<<0;
  b = reg68.d[reg9]<<0;
  CMPL(a,b);
}

void lineB13(u32 reg9, u32 reg0)
{
  /* CMP.L <Ae>,Dn */
  s32 a,b;
  u32 addr;
  addr = get_eal[3](reg0);
  a = read_L(addr)<<0;
  b = reg68.d[reg9]<<0;
  CMPL(a,b);
}

void lineB14(u32 reg9, u32 reg0)
{
  /* CMP.L <Ae>,Dn */
  s32 a,b;
  u32 addr;
  addr = get_eal[4](reg0);
  a = read_L(addr)<<0;
  b = reg68.d[reg9]<<0;
  CMPL(a,b);
}

void lineB15(u32 reg9, u32 reg0)
{
  /* CMP.L <Ae>,Dn */
  s32 a,b;
  u32 addr;
  addr = get_eal[5](reg0);
  a = read_L(addr)<<0;
  b = reg68.d[reg9]<<0;
  CMPL(a,b);
}

void lineB16(u32 reg9, u32 reg0)
{
  /* CMP.L <Ae>,Dn */
  s32 a,b;
  u32 addr;
  addr = get_eal[6](reg0);
  a = read_L(addr)<<0;
  b = reg68.d[reg9]<<0;
  CMPL(a,b);
}

void lineB17(u32 reg9, u32 reg0)
{
  /* CMP.L <Ae>,Dn */
  s32 a,b;
  u32 addr;
  addr = get_eal[7](reg0);
  a = read_L(addr)<<0;
  b = reg68.d[reg9]<<0;
  CMPL(a,b);
}

void lineB18(u32 reg9, u32 reg0)
{
  /* CMP.W Dx,Ay */
  s32 a,b;
  a = reg68.d[reg0]<<16;
  b = reg68.a[reg9];
  CMPAW(a,b);
}

void lineB19(u32 reg9, u32 reg0)
{
  /* CMP.W Ax,Ay */
  s32 a,b;
  a = reg68.a[reg0]<<16;
  b = reg68.a[reg9];
  CMPAW(a,b);
}

void lineB1A(u32 reg9, u32 reg0)
{
  /* CMP.W <Ae>,An */
  s32 a,b;
  u32 addr;
  addr = get_eaw[2](reg0);
  a = read_W(addr)<<16;
  b = reg68.a[reg9];
  CMPAW(a,b);
}

void lineB1B(u32 reg9, u32 reg0)
{
  /* CMP.W <Ae>,An */
  s32 a,b;
  u32 addr;
  addr = get_eaw[3](reg0);
  a = read_W(addr)<<16;
  b = reg68.a[reg9];
  CMPAW(a,b);
}

void lineB1C(u32 reg9, u32 reg0)
{
  /* CMP.W <Ae>,An */
  s32 a,b;
  u32 addr;
  addr = get_eaw[4](reg0);
  a = read_W(addr)<<16;
  b = reg68.a[reg9];
  CMPAW(a,b);
}

void lineB1D(u32 reg9, u32 reg0)
{
  /* CMP.W <Ae>,An */
  s32 a,b;
  u32 addr;
  addr = get_eaw[5](reg0);
  a = read_W(addr)<<16;
  b = reg68.a[reg9];
  CMPAW(a,b);
}

void lineB1E(u32 reg9, u32 reg0)
{
  /* CMP.W <Ae>,An */
  s32 a,b;
  u32 addr;
  addr = get_eaw[6](reg0);
  a = read_W(addr)<<16;
  b = reg68.a[reg9];
  CMPAW(a,b);
}

void lineB1F(u32 reg9, u32 reg0)
{
  /* CMP.W <Ae>,An */
  s32 a,b;
  u32 addr;
  addr = get_eaw[7](reg0);
  a = read_W(addr)<<16;
  b = reg68.a[reg9];
  CMPAW(a,b);
}

void lineB20(u32 reg9, u32 reg0)
{
  /* EOR.B Dx,Dy */
  s32 a,b,s;
  a = reg68.d[reg9]<<24;
  b = reg68.d[reg0]<<24;
  EORB(s,a,b);
  reg68.d[reg0] = (reg68.d[reg0]&0xffffff00) + ((u32)s>>24);
}

void lineB21(u32 reg9, u32 reg0)
{
  /* CMPM.B (Ay)+,(Ax)+ */
  s32 x,y;
  y = read_B(reg68.a[reg0]-=1);
  x = read_B(reg68.a[reg9]-=1);
  CMPB(y,x);
}

void lineB22(u32 reg9, u32 reg0)
{
  /* EOR.B Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<24;
  addr = get_eab[2](reg0);
  b = read_B(addr)<<24;
  EORB(s,a,b);
  write_B(addr,(u32)s>>24);
}

void lineB23(u32 reg9, u32 reg0)
{
  /* EOR.B Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<24;
  addr = get_eab[3](reg0);
  b = read_B(addr)<<24;
  EORB(s,a,b);
  write_B(addr,(u32)s>>24);
}

void lineB24(u32 reg9, u32 reg0)
{
  /* EOR.B Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<24;
  addr = get_eab[4](reg0);
  b = read_B(addr)<<24;
  EORB(s,a,b);
  write_B(addr,(u32)s>>24);
}

void lineB25(u32 reg9, u32 reg0)
{
  /* EOR.B Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<24;
  addr = get_eab[5](reg0);
  b = read_B(addr)<<24;
  EORB(s,a,b);
  write_B(addr,(u32)s>>24);
}

void lineB26(u32 reg9, u32 reg0)
{
  /* EOR.B Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<24;
  addr = get_eab[6](reg0);
  b = read_B(addr)<<24;
  EORB(s,a,b);
  write_B(addr,(u32)s>>24);
}

void lineB27(u32 reg9, u32 reg0)
{
  /* EOR.B Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<24;
  addr = get_eab[7](reg0);
  b = read_B(addr)<<24;
  EORB(s,a,b);
  write_B(addr,(u32)s>>24);
}

void lineB28(u32 reg9, u32 reg0)
{
  /* EOR.W Dx,Dy */
  s32 a,b,s;
  a = reg68.d[reg9]<<16;
  b = reg68.d[reg0]<<16;
  EORW(s,a,b);
  reg68.d[reg0] = (reg68.d[reg0]&0xffff0000) + ((u32)s>>16);
}

void lineB29(u32 reg9, u32 reg0)
{
  /* CMPM.W (Ay)+,(Ax)+ */
  s32 x,y;
  y = read_W(reg68.a[reg0]-=2);
  x = read_W(reg68.a[reg9]-=2);
  CMPW(y,x);
}

void lineB2A(u32 reg9, u32 reg0)
{
  /* EOR.W Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<16;
  addr = get_eaw[2](reg0);
  b = read_W(addr)<<16;
  EORW(s,a,b);
  write_W(addr,(u32)s>>16);
}

void lineB2B(u32 reg9, u32 reg0)
{
  /* EOR.W Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<16;
  addr = get_eaw[3](reg0);
  b = read_W(addr)<<16;
  EORW(s,a,b);
  write_W(addr,(u32)s>>16);
}

void lineB2C(u32 reg9, u32 reg0)
{
  /* EOR.W Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<16;
  addr = get_eaw[4](reg0);
  b = read_W(addr)<<16;
  EORW(s,a,b);
  write_W(addr,(u32)s>>16);
}

void lineB2D(u32 reg9, u32 reg0)
{
  /* EOR.W Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<16;
  addr = get_eaw[5](reg0);
  b = read_W(addr)<<16;
  EORW(s,a,b);
  write_W(addr,(u32)s>>16);
}

void lineB2E(u32 reg9, u32 reg0)
{
  /* EOR.W Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<16;
  addr = get_eaw[6](reg0);
  b = read_W(addr)<<16;
  EORW(s,a,b);
  write_W(addr,(u32)s>>16);
}

void lineB2F(u32 reg9, u32 reg0)
{
  /* EOR.W Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<16;
  addr = get_eaw[7](reg0);
  b = read_W(addr)<<16;
  EORW(s,a,b);
  write_W(addr,(u32)s>>16);
}

void lineB30(u32 reg9, u32 reg0)
{
  /* EOR.L Dx,Dy */
  s32 a,b,s;
  a = reg68.d[reg9]<<0;
  b = reg68.d[reg0]<<0;
  EORL(s,a,b);
  reg68.d[reg0] = (reg68.d[reg0]&0) + ((u32)s>>0);
}

void lineB31(u32 reg9, u32 reg0)
{
  /* CMPM.L (Ay)+,(Ax)+ */
  s32 x,y;
  y = read_L(reg68.a[reg0]-=4);
  x = read_L(reg68.a[reg9]-=4);
  CMPL(y,x);
}

void lineB32(u32 reg9, u32 reg0)
{
  /* EOR.L Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<0;
  addr = get_eal[2](reg0);
  b = read_L(addr)<<0;
  EORL(s,a,b);
  write_L(addr,(u32)s>>0);
}

void lineB33(u32 reg9, u32 reg0)
{
  /* EOR.L Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<0;
  addr = get_eal[3](reg0);
  b = read_L(addr)<<0;
  EORL(s,a,b);
  write_L(addr,(u32)s>>0);
}

void lineB34(u32 reg9, u32 reg0)
{
  /* EOR.L Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<0;
  addr = get_eal[4](reg0);
  b = read_L(addr)<<0;
  EORL(s,a,b);
  write_L(addr,(u32)s>>0);
}

void lineB35(u32 reg9, u32 reg0)
{
  /* EOR.L Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<0;
  addr = get_eal[5](reg0);
  b = read_L(addr)<<0;
  EORL(s,a,b);
  write_L(addr,(u32)s>>0);
}

void lineB36(u32 reg9, u32 reg0)
{
  /* EOR.L Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<0;
  addr = get_eal[6](reg0);
  b = read_L(addr)<<0;
  EORL(s,a,b);
  write_L(addr,(u32)s>>0);
}

void lineB37(u32 reg9, u32 reg0)
{
  /* EOR.L Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<0;
  addr = get_eal[7](reg0);
  b = read_L(addr)<<0;
  EORL(s,a,b);
  write_L(addr,(u32)s>>0);
}

void lineB38(u32 reg9, u32 reg0)
{
  /* CMP.L Dx,Ay */
  s32 a,b;
  a = reg68.d[reg0]<<0;
  b = reg68.a[reg9];
  CMPAL(a,b);
}

void lineB39(u32 reg9, u32 reg0)
{
  /* CMP.L Ax,Ay */
  s32 a,b;
  a = reg68.a[reg0]<<0;
  b = reg68.a[reg9];
  CMPAL(a,b);
}

void lineB3A(u32 reg9, u32 reg0)
{
  /* CMP.L <Ae>,An */
  s32 a,b;
  u32 addr;
  addr = get_eal[2](reg0);
  a = read_L(addr)<<0;
  b = reg68.a[reg9];
  CMPAL(a,b);
}

void lineB3B(u32 reg9, u32 reg0)
{
  /* CMP.L <Ae>,An */
  s32 a,b;
  u32 addr;
  addr = get_eal[3](reg0);
  a = read_L(addr)<<0;
  b = reg68.a[reg9];
  CMPAL(a,b);
}

void lineB3C(u32 reg9, u32 reg0)
{
  /* CMP.L <Ae>,An */
  s32 a,b;
  u32 addr;
  addr = get_eal[4](reg0);
  a = read_L(addr)<<0;
  b = reg68.a[reg9];
  CMPAL(a,b);
}

void lineB3D(u32 reg9, u32 reg0)
{
  /* CMP.L <Ae>,An */
  s32 a,b;
  u32 addr;
  addr = get_eal[5](reg0);
  a = read_L(addr)<<0;
  b = reg68.a[reg9];
  CMPAL(a,b);
}

void lineB3E(u32 reg9, u32 reg0)
{
  /* CMP.L <Ae>,An */
  s32 a,b;
  u32 addr;
  addr = get_eal[6](reg0);
  a = read_L(addr)<<0;
  b = reg68.a[reg9];
  CMPAL(a,b);
}

void lineB3F(u32 reg9, u32 reg0)
{
  /* CMP.L <Ae>,An */
  s32 a,b;
  u32 addr;
  addr = get_eal[7](reg0);
  a = read_L(addr)<<0;
  b = reg68.a[reg9];
  CMPAL(a,b);
}

void lineC00(u32 reg9, u32 reg0)
{
  /* AND.B Dx,Dy */
  s32 a,b,s;
  a = reg68.d[reg0]<<24;
  b = reg68.d[reg9]<<24;
  ANDB(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffffff00) + ((u32)s>>24);
}

void lineC01(u32 reg9, u32 reg0)
{
  /*ILLEGAL in EXG*/
  ILLEGAL
}

void lineC02(u32 reg9, u32 reg0)
{
  /* AND.B <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eab[2](reg0);
  a = read_B(addr)<<24;
  b = reg68.d[reg9]<<24;
  ANDB(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffffff00) + ((u32)s>>24);
}

void lineC03(u32 reg9, u32 reg0)
{
  /* AND.B <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eab[3](reg0);
  a = read_B(addr)<<24;
  b = reg68.d[reg9]<<24;
  ANDB(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffffff00) + ((u32)s>>24);
}

void lineC04(u32 reg9, u32 reg0)
{
  /* AND.B <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eab[4](reg0);
  a = read_B(addr)<<24;
  b = reg68.d[reg9]<<24;
  ANDB(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffffff00) + ((u32)s>>24);
}

void lineC05(u32 reg9, u32 reg0)
{
  /* AND.B <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eab[5](reg0);
  a = read_B(addr)<<24;
  b = reg68.d[reg9]<<24;
  ANDB(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffffff00) + ((u32)s>>24);
}

void lineC06(u32 reg9, u32 reg0)
{
  /* AND.B <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eab[6](reg0);
  a = read_B(addr)<<24;
  b = reg68.d[reg9]<<24;
  ANDB(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffffff00) + ((u32)s>>24);
}

void lineC07(u32 reg9, u32 reg0)
{
  /* AND.B <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eab[7](reg0);
  a = read_B(addr)<<24;
  b = reg68.d[reg9]<<24;
  ANDB(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffffff00) + ((u32)s>>24);
}

void lineC08(u32 reg9, u32 reg0)
{
  /* AND.W Dx,Dy */
  s32 a,b,s;
  a = reg68.d[reg0]<<16;
  b = reg68.d[reg9]<<16;
  ANDW(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffff0000) + ((u32)s>>16);
}

void lineC09(u32 reg9, u32 reg0)
{
  /* EXG Ax,Ay */
  EXG(reg68.a[reg9],reg68.a[reg0]);
}

void lineC0A(u32 reg9, u32 reg0)
{
  /* AND.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[2](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  ANDW(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffff0000) + ((u32)s>>16);
}

void lineC0B(u32 reg9, u32 reg0)
{
  /* AND.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[3](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  ANDW(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffff0000) + ((u32)s>>16);
}

void lineC0C(u32 reg9, u32 reg0)
{
  /* AND.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[4](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  ANDW(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffff0000) + ((u32)s>>16);
}

void lineC0D(u32 reg9, u32 reg0)
{
  /* AND.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[5](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  ANDW(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffff0000) + ((u32)s>>16);
}

void lineC0E(u32 reg9, u32 reg0)
{
  /* AND.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[6](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  ANDW(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffff0000) + ((u32)s>>16);
}

void lineC0F(u32 reg9, u32 reg0)
{
  /* AND.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[7](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  ANDW(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffff0000) + ((u32)s>>16);
}

void lineC10(u32 reg9, u32 reg0)
{
  /* AND.L Dx,Dy */
  s32 a,b,s;
  a = reg68.d[reg0]<<0;
  b = reg68.d[reg9]<<0;
  ANDL(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0) + ((u32)s>>0);
}

void lineC11(u32 reg9, u32 reg0)
{
  /* EXG Dx,Ay */
  EXG(reg68.d[reg9],reg68.a[reg0]);
}

void lineC12(u32 reg9, u32 reg0)
{
  /* AND.L <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eal[2](reg0);
  a = read_L(addr)<<0;
  b = reg68.d[reg9]<<0;
  ANDL(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0) + ((u32)s>>0);
}

void lineC13(u32 reg9, u32 reg0)
{
  /* AND.L <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eal[3](reg0);
  a = read_L(addr)<<0;
  b = reg68.d[reg9]<<0;
  ANDL(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0) + ((u32)s>>0);
}

void lineC14(u32 reg9, u32 reg0)
{
  /* AND.L <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eal[4](reg0);
  a = read_L(addr)<<0;
  b = reg68.d[reg9]<<0;
  ANDL(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0) + ((u32)s>>0);
}

void lineC15(u32 reg9, u32 reg0)
{
  /* AND.L <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eal[5](reg0);
  a = read_L(addr)<<0;
  b = reg68.d[reg9]<<0;
  ANDL(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0) + ((u32)s>>0);
}

void lineC16(u32 reg9, u32 reg0)
{
  /* AND.L <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eal[6](reg0);
  a = read_L(addr)<<0;
  b = reg68.d[reg9]<<0;
  ANDL(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0) + ((u32)s>>0);
}

void lineC17(u32 reg9, u32 reg0)
{
  /* AND.L <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eal[7](reg0);
  a = read_L(addr)<<0;
  b = reg68.d[reg9]<<0;
  ANDL(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0) + ((u32)s>>0);
}

void lineC18(u32 reg9, u32 reg0)
{
  /* MULU.W Dx,Dy */
  s32 a,b,s;
  a = reg68.d[reg0]<<16;
  b = reg68.d[reg9]<<16;
  MULUW(s,a,b);
  reg68.d[reg9] = s;
}

void lineC19(u32 reg9, u32 reg0)
{
  /* MULU.W Ax,Dy */
  s32 a,b,s;
  a = reg68.a[reg0]<<16;
  b = reg68.d[reg9]<<16;
  MULUW(s,a,b);
  reg68.d[reg9] = s;
}

void lineC1A(u32 reg9, u32 reg0)
{
  /* MULU.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[2](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  MULUW(s,a,b);
  reg68.d[reg9] = s;
}

void lineC1B(u32 reg9, u32 reg0)
{
  /* MULU.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[3](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  MULUW(s,a,b);
  reg68.d[reg9] = s;
}

void lineC1C(u32 reg9, u32 reg0)
{
  /* MULU.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[4](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  MULUW(s,a,b);
  reg68.d[reg9] = s;
}

void lineC1D(u32 reg9, u32 reg0)
{
  /* MULU.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[5](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  MULUW(s,a,b);
  reg68.d[reg9] = s;
}

void lineC1E(u32 reg9, u32 reg0)
{
  /* MULU.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[6](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  MULUW(s,a,b);
  reg68.d[reg9] = s;
}

void lineC1F(u32 reg9, u32 reg0)
{
  /* MULU.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[7](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  MULUW(s,a,b);
  reg68.d[reg9] = s;
}

void lineC20(u32 reg9, u32 reg0)
{
  /* ABCD Dy,Dx */
  reg0=reg0; reg9=reg9;
}

void lineC21(u32 reg9, u32 reg0)
{
  /* ABCD -(Ay),-(Ax) */
  reg68.a[reg0] -= 2;
  reg68.a[reg9] -= 2;
}

void lineC22(u32 reg9, u32 reg0)
{
  /* AND.B Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<24;
  addr = get_eab[2](reg0);
  b = read_B(addr)<<24;
  ANDB(s,a,b);
  write_B(addr,(u32)s>>24);
}

void lineC23(u32 reg9, u32 reg0)
{
  /* AND.B Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<24;
  addr = get_eab[3](reg0);
  b = read_B(addr)<<24;
  ANDB(s,a,b);
  write_B(addr,(u32)s>>24);
}

void lineC24(u32 reg9, u32 reg0)
{
  /* AND.B Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<24;
  addr = get_eab[4](reg0);
  b = read_B(addr)<<24;
  ANDB(s,a,b);
  write_B(addr,(u32)s>>24);
}

void lineC25(u32 reg9, u32 reg0)
{
  /* AND.B Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<24;
  addr = get_eab[5](reg0);
  b = read_B(addr)<<24;
  ANDB(s,a,b);
  write_B(addr,(u32)s>>24);
}

void lineC26(u32 reg9, u32 reg0)
{
  /* AND.B Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<24;
  addr = get_eab[6](reg0);
  b = read_B(addr)<<24;
  ANDB(s,a,b);
  write_B(addr,(u32)s>>24);
}

void lineC27(u32 reg9, u32 reg0)
{
  /* AND.B Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<24;
  addr = get_eab[7](reg0);
  b = read_B(addr)<<24;
  ANDB(s,a,b);
  write_B(addr,(u32)s>>24);
}

void lineC28(u32 reg9, u32 reg0)
{
  /* EXG Dx,Dy */
  EXG(reg68.d[reg9],reg68.d[reg0]);
}

void lineC29(u32 reg9, u32 reg0)
{
  /* EXG Ax,Ay */
  EXG(reg68.a[reg9],reg68.a[reg0]);
}

void lineC2A(u32 reg9, u32 reg0)
{
  /* AND.W Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<16;
  addr = get_eaw[2](reg0);
  b = read_W(addr)<<16;
  ANDW(s,a,b);
  write_W(addr,(u32)s>>16);
}

void lineC2B(u32 reg9, u32 reg0)
{
  /* AND.W Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<16;
  addr = get_eaw[3](reg0);
  b = read_W(addr)<<16;
  ANDW(s,a,b);
  write_W(addr,(u32)s>>16);
}

void lineC2C(u32 reg9, u32 reg0)
{
  /* AND.W Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<16;
  addr = get_eaw[4](reg0);
  b = read_W(addr)<<16;
  ANDW(s,a,b);
  write_W(addr,(u32)s>>16);
}

void lineC2D(u32 reg9, u32 reg0)
{
  /* AND.W Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<16;
  addr = get_eaw[5](reg0);
  b = read_W(addr)<<16;
  ANDW(s,a,b);
  write_W(addr,(u32)s>>16);
}

void lineC2E(u32 reg9, u32 reg0)
{
  /* AND.W Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<16;
  addr = get_eaw[6](reg0);
  b = read_W(addr)<<16;
  ANDW(s,a,b);
  write_W(addr,(u32)s>>16);
}

void lineC2F(u32 reg9, u32 reg0)
{
  /* AND.W Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<16;
  addr = get_eaw[7](reg0);
  b = read_W(addr)<<16;
  ANDW(s,a,b);
  write_W(addr,(u32)s>>16);
}

void lineC30(u32 reg9, u32 reg0)
{
  /* AND.L Dx,Dy */
  s32 a,b,s;
  a = reg68.d[reg9]<<0;
  b = reg68.d[reg0]<<0;
  ANDL(s,a,b);
  reg68.d[reg0] = (reg68.d[reg0]&0) + ((u32)s>>0);
}

void lineC31(u32 reg9, u32 reg0)
{
  /* EXG Dx,Ay */
  EXG(reg68.d[reg9],reg68.a[reg0]);
}

void lineC32(u32 reg9, u32 reg0)
{
  /* AND.L Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<0;
  addr = get_eal[2](reg0);
  b = read_L(addr)<<0;
  ANDL(s,a,b);
  write_L(addr,(u32)s>>0);
}

void lineC33(u32 reg9, u32 reg0)
{
  /* AND.L Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<0;
  addr = get_eal[3](reg0);
  b = read_L(addr)<<0;
  ANDL(s,a,b);
  write_L(addr,(u32)s>>0);
}

void lineC34(u32 reg9, u32 reg0)
{
  /* AND.L Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<0;
  addr = get_eal[4](reg0);
  b = read_L(addr)<<0;
  ANDL(s,a,b);
  write_L(addr,(u32)s>>0);
}

void lineC35(u32 reg9, u32 reg0)
{
  /* AND.L Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<0;
  addr = get_eal[5](reg0);
  b = read_L(addr)<<0;
  ANDL(s,a,b);
  write_L(addr,(u32)s>>0);
}

void lineC36(u32 reg9, u32 reg0)
{
  /* AND.L Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<0;
  addr = get_eal[6](reg0);
  b = read_L(addr)<<0;
  ANDL(s,a,b);
  write_L(addr,(u32)s>>0);
}

void lineC37(u32 reg9, u32 reg0)
{
  /* AND.L Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<0;
  addr = get_eal[7](reg0);
  b = read_L(addr)<<0;
  ANDL(s,a,b);
  write_L(addr,(u32)s>>0);
}

void lineC38(u32 reg9, u32 reg0)
{
  /* MULS.W Dx,Dy */
  s32 a,b,s;
  a = reg68.d[reg0]<<16;
  b = reg68.d[reg9]<<16;
  MULSW(s,a,b);
  reg68.d[reg9] = s;
}

void lineC39(u32 reg9, u32 reg0)
{
  /* MULS.W Ax,Dy */
  s32 a,b,s;
  a = reg68.a[reg0]<<16;
  b = reg68.d[reg9]<<16;
  MULSW(s,a,b);
  reg68.d[reg9] = s;
}

void lineC3A(u32 reg9, u32 reg0)
{
  /* MULS.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[2](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  MULSW(s,a,b);
  reg68.d[reg9] = s;
}

void lineC3B(u32 reg9, u32 reg0)
{
  /* MULS.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[3](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  MULSW(s,a,b);
  reg68.d[reg9] = s;
}

void lineC3C(u32 reg9, u32 reg0)
{
  /* MULS.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[4](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  MULSW(s,a,b);
  reg68.d[reg9] = s;
}

void lineC3D(u32 reg9, u32 reg0)
{
  /* MULS.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[5](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  MULSW(s,a,b);
  reg68.d[reg9] = s;
}

void lineC3E(u32 reg9, u32 reg0)
{
  /* MULS.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[6](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  MULSW(s,a,b);
  reg68.d[reg9] = s;
}

void lineC3F(u32 reg9, u32 reg0)
{
  /* MULS.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[7](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  MULSW(s,a,b);
  reg68.d[reg9] = s;
}

void lineD00(u32 reg9, u32 reg0)
{
  /* ADD.B Dx,Dy */
  s32 a,b,s;
  a = reg68.d[reg0]<<24;
  b = reg68.d[reg9]<<24;
  ADDB(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffffff00) + ((u32)s>>24);
}

void lineD01(u32 reg9, u32 reg0)
{
  /* ADD.B Ax,Dy */
  s32 a,b,s;
  a = reg68.a[reg0]<<24;
  b = reg68.d[reg9]<<24;
  ADDB(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffffff00) + ((u32)s>>24);
}

void lineD02(u32 reg9, u32 reg0)
{
  /* ADD.B <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eab[2](reg0);
  a = read_B(addr)<<24;
  b = reg68.d[reg9]<<24;
  ADDB(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffffff00) + ((u32)s>>24);
}

void lineD03(u32 reg9, u32 reg0)
{
  /* ADD.B <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eab[3](reg0);
  a = read_B(addr)<<24;
  b = reg68.d[reg9]<<24;
  ADDB(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffffff00) + ((u32)s>>24);
}

void lineD04(u32 reg9, u32 reg0)
{
  /* ADD.B <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eab[4](reg0);
  a = read_B(addr)<<24;
  b = reg68.d[reg9]<<24;
  ADDB(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffffff00) + ((u32)s>>24);
}

void lineD05(u32 reg9, u32 reg0)
{
  /* ADD.B <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eab[5](reg0);
  a = read_B(addr)<<24;
  b = reg68.d[reg9]<<24;
  ADDB(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffffff00) + ((u32)s>>24);
}

void lineD06(u32 reg9, u32 reg0)
{
  /* ADD.B <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eab[6](reg0);
  a = read_B(addr)<<24;
  b = reg68.d[reg9]<<24;
  ADDB(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffffff00) + ((u32)s>>24);
}

void lineD07(u32 reg9, u32 reg0)
{
  /* ADD.B <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eab[7](reg0);
  a = read_B(addr)<<24;
  b = reg68.d[reg9]<<24;
  ADDB(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffffff00) + ((u32)s>>24);
}

void lineD08(u32 reg9, u32 reg0)
{
  /* ADD.W Dx,Dy */
  s32 a,b,s;
  a = reg68.d[reg0]<<16;
  b = reg68.d[reg9]<<16;
  ADDW(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffff0000) + ((u32)s>>16);
}

void lineD09(u32 reg9, u32 reg0)
{
  /* ADD.W Ax,Dy */
  s32 a,b,s;
  a = reg68.a[reg0]<<16;
  b = reg68.d[reg9]<<16;
  ADDW(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffff0000) + ((u32)s>>16);
}

void lineD0A(u32 reg9, u32 reg0)
{
  /* ADD.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[2](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  ADDW(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffff0000) + ((u32)s>>16);
}

void lineD0B(u32 reg9, u32 reg0)
{
  /* ADD.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[3](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  ADDW(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffff0000) + ((u32)s>>16);
}

void lineD0C(u32 reg9, u32 reg0)
{
  /* ADD.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[4](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  ADDW(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffff0000) + ((u32)s>>16);
}

void lineD0D(u32 reg9, u32 reg0)
{
  /* ADD.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[5](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  ADDW(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffff0000) + ((u32)s>>16);
}

void lineD0E(u32 reg9, u32 reg0)
{
  /* ADD.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[6](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  ADDW(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffff0000) + ((u32)s>>16);
}

void lineD0F(u32 reg9, u32 reg0)
{
  /* ADD.W <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[7](reg0);
  a = read_W(addr)<<16;
  b = reg68.d[reg9]<<16;
  ADDW(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffff0000) + ((u32)s>>16);
}

void lineD10(u32 reg9, u32 reg0)
{
  /* ADD.L Dx,Dy */
  s32 a,b,s;
  a = reg68.d[reg0]<<0;
  b = reg68.d[reg9]<<0;
  ADDL(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0) + ((u32)s>>0);
}

void lineD11(u32 reg9, u32 reg0)
{
  /* ADD.L Ax,Dy */
  s32 a,b,s;
  a = reg68.a[reg0]<<0;
  b = reg68.d[reg9]<<0;
  ADDL(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0) + ((u32)s>>0);
}

void lineD12(u32 reg9, u32 reg0)
{
  /* ADD.L <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eal[2](reg0);
  a = read_L(addr)<<0;
  b = reg68.d[reg9]<<0;
  ADDL(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0) + ((u32)s>>0);
}

void lineD13(u32 reg9, u32 reg0)
{
  /* ADD.L <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eal[3](reg0);
  a = read_L(addr)<<0;
  b = reg68.d[reg9]<<0;
  ADDL(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0) + ((u32)s>>0);
}

void lineD14(u32 reg9, u32 reg0)
{
  /* ADD.L <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eal[4](reg0);
  a = read_L(addr)<<0;
  b = reg68.d[reg9]<<0;
  ADDL(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0) + ((u32)s>>0);
}

void lineD15(u32 reg9, u32 reg0)
{
  /* ADD.L <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eal[5](reg0);
  a = read_L(addr)<<0;
  b = reg68.d[reg9]<<0;
  ADDL(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0) + ((u32)s>>0);
}

void lineD16(u32 reg9, u32 reg0)
{
  /* ADD.L <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eal[6](reg0);
  a = read_L(addr)<<0;
  b = reg68.d[reg9]<<0;
  ADDL(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0) + ((u32)s>>0);
}

void lineD17(u32 reg9, u32 reg0)
{
  /* ADD.L <Ae>,Dn */
  s32 a,b,s;
  u32 addr;
  addr = get_eal[7](reg0);
  a = read_L(addr)<<0;
  b = reg68.d[reg9]<<0;
  ADDL(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0) + ((u32)s>>0);
}

void lineD18(u32 reg9, u32 reg0)
{
  /* ADD.W Dx,Ay */
  s32 a,b,s;
  a = reg68.d[reg0]<<16;
  b = reg68.a[reg9];
  ADDAW(s,a,b);
  reg68.a[reg9] = s;
}

void lineD19(u32 reg9, u32 reg0)
{
  /* ADD.W Ax,Ay */
  s32 a,b,s;
  a = reg68.a[reg0]<<16;
  b = reg68.a[reg9];
  ADDAW(s,a,b);
  reg68.a[reg9] = s;
}

void lineD1A(u32 reg9, u32 reg0)
{
  /* ADD.W <Ae>,An */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[2](reg0);
  a = read_W(addr)<<16;
  b = reg68.a[reg9];
  ADDAW(s,a,b);
  reg68.a[reg9] = s;
}

void lineD1B(u32 reg9, u32 reg0)
{
  /* ADD.W <Ae>,An */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[3](reg0);
  a = read_W(addr)<<16;
  b = reg68.a[reg9];
  ADDAW(s,a,b);
  reg68.a[reg9] = s;
}

void lineD1C(u32 reg9, u32 reg0)
{
  /* ADD.W <Ae>,An */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[4](reg0);
  a = read_W(addr)<<16;
  b = reg68.a[reg9];
  ADDAW(s,a,b);
  reg68.a[reg9] = s;
}

void lineD1D(u32 reg9, u32 reg0)
{
  /* ADD.W <Ae>,An */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[5](reg0);
  a = read_W(addr)<<16;
  b = reg68.a[reg9];
  ADDAW(s,a,b);
  reg68.a[reg9] = s;
}

void lineD1E(u32 reg9, u32 reg0)
{
  /* ADD.W <Ae>,An */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[6](reg0);
  a = read_W(addr)<<16;
  b = reg68.a[reg9];
  ADDAW(s,a,b);
  reg68.a[reg9] = s;
}

void lineD1F(u32 reg9, u32 reg0)
{
  /* ADD.W <Ae>,An */
  s32 a,b,s;
  u32 addr;
  addr = get_eaw[7](reg0);
  a = read_W(addr)<<16;
  b = reg68.a[reg9];
  ADDAW(s,a,b);
  reg68.a[reg9] = s;
}

void lineD20(u32 reg9, u32 reg0)
{
  s32 a,b,s;
  a = reg68.d[reg0]<<24;
  b = reg68.d[reg9]<<24;
  ADDXB(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffffff00) + ((u32)s>>24);
}

void lineD21(u32 reg9, u32 reg0)
{
  s32 a,b,s;
  a = read_B(reg68.a[reg0]-=1)<<24;
  b = read_B(reg68.a[reg9]-=1)<<24;
  ADDXB(s,a,b);
  write_B(reg68.a[reg9],(u32)s>>24);
}

void lineD22(u32 reg9, u32 reg0)
{
  /* ADD.B Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<24;
  addr = get_eab[2](reg0);
  b = read_B(addr)<<24;
  ADDB(s,a,b);
  write_B(addr,(u32)s>>24);
}

void lineD23(u32 reg9, u32 reg0)
{
  /* ADD.B Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<24;
  addr = get_eab[3](reg0);
  b = read_B(addr)<<24;
  ADDB(s,a,b);
  write_B(addr,(u32)s>>24);
}

void lineD24(u32 reg9, u32 reg0)
{
  /* ADD.B Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<24;
  addr = get_eab[4](reg0);
  b = read_B(addr)<<24;
  ADDB(s,a,b);
  write_B(addr,(u32)s>>24);
}

void lineD25(u32 reg9, u32 reg0)
{
  /* ADD.B Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<24;
  addr = get_eab[5](reg0);
  b = read_B(addr)<<24;
  ADDB(s,a,b);
  write_B(addr,(u32)s>>24);
}

void lineD26(u32 reg9, u32 reg0)
{
  /* ADD.B Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<24;
  addr = get_eab[6](reg0);
  b = read_B(addr)<<24;
  ADDB(s,a,b);
  write_B(addr,(u32)s>>24);
}

void lineD27(u32 reg9, u32 reg0)
{
  /* ADD.B Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<24;
  addr = get_eab[7](reg0);
  b = read_B(addr)<<24;
  ADDB(s,a,b);
  write_B(addr,(u32)s>>24);
}

void lineD28(u32 reg9, u32 reg0)
{
  s32 a,b,s;
  a = reg68.d[reg0]<<16;
  b = reg68.d[reg9]<<16;
  ADDXW(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0xffff0000) + ((u32)s>>16);
}

void lineD29(u32 reg9, u32 reg0)
{
  s32 a,b,s;
  a = read_W(reg68.a[reg0]-=2)<<16;
  b = read_W(reg68.a[reg9]-=2)<<16;
  ADDXW(s,a,b);
  write_W(reg68.a[reg9],(u32)s>>16);
}

void lineD2A(u32 reg9, u32 reg0)
{
  /* ADD.W Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<16;
  addr = get_eaw[2](reg0);
  b = read_W(addr)<<16;
  ADDW(s,a,b);
  write_W(addr,(u32)s>>16);
}

void lineD2B(u32 reg9, u32 reg0)
{
  /* ADD.W Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<16;
  addr = get_eaw[3](reg0);
  b = read_W(addr)<<16;
  ADDW(s,a,b);
  write_W(addr,(u32)s>>16);
}

void lineD2C(u32 reg9, u32 reg0)
{
  /* ADD.W Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<16;
  addr = get_eaw[4](reg0);
  b = read_W(addr)<<16;
  ADDW(s,a,b);
  write_W(addr,(u32)s>>16);
}

void lineD2D(u32 reg9, u32 reg0)
{
  /* ADD.W Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<16;
  addr = get_eaw[5](reg0);
  b = read_W(addr)<<16;
  ADDW(s,a,b);
  write_W(addr,(u32)s>>16);
}

void lineD2E(u32 reg9, u32 reg0)
{
  /* ADD.W Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<16;
  addr = get_eaw[6](reg0);
  b = read_W(addr)<<16;
  ADDW(s,a,b);
  write_W(addr,(u32)s>>16);
}

void lineD2F(u32 reg9, u32 reg0)
{
  /* ADD.W Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<16;
  addr = get_eaw[7](reg0);
  b = read_W(addr)<<16;
  ADDW(s,a,b);
  write_W(addr,(u32)s>>16);
}

void lineD30(u32 reg9, u32 reg0)
{
  s32 a,b,s;
  a = reg68.d[reg0]<<0;
  b = reg68.d[reg9]<<0;
  ADDXL(s,a,b);
  reg68.d[reg9] = (reg68.d[reg9]&0) + ((u32)s>>0);
}

void lineD31(u32 reg9, u32 reg0)
{
  s32 a,b,s;
  a = read_L(reg68.a[reg0]-=4)<<0;
  b = read_L(reg68.a[reg9]-=4)<<0;
  ADDXL(s,a,b);
  write_L(reg68.a[reg9],(u32)s>>0);
}

void lineD32(u32 reg9, u32 reg0)
{
  /* ADD.L Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<0;
  addr = get_eal[2](reg0);
  b = read_L(addr)<<0;
  ADDL(s,a,b);
  write_L(addr,(u32)s>>0);
}

void lineD33(u32 reg9, u32 reg0)
{
  /* ADD.L Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<0;
  addr = get_eal[3](reg0);
  b = read_L(addr)<<0;
  ADDL(s,a,b);
  write_L(addr,(u32)s>>0);
}

void lineD34(u32 reg9, u32 reg0)
{
  /* ADD.L Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<0;
  addr = get_eal[4](reg0);
  b = read_L(addr)<<0;
  ADDL(s,a,b);
  write_L(addr,(u32)s>>0);
}

void lineD35(u32 reg9, u32 reg0)
{
  /* ADD.L Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<0;
  addr = get_eal[5](reg0);
  b = read_L(addr)<<0;
  ADDL(s,a,b);
  write_L(addr,(u32)s>>0);
}

void lineD36(u32 reg9, u32 reg0)
{
  /* ADD.L Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<0;
  addr = get_eal[6](reg0);
  b = read_L(addr)<<0;
  ADDL(s,a,b);
  write_L(addr,(u32)s>>0);
}

void lineD37(u32 reg9, u32 reg0)
{
  /* ADD.L Dn,<Ae> */
  s32 a,b,s;
  u32 addr;
  a = reg68.d[reg9]<<0;
  addr = get_eal[7](reg0);
  b = read_L(addr)<<0;
  ADDL(s,a,b);
  write_L(addr,(u32)s>>0);
}

void lineD38(u32 reg9, u32 reg0)
{
  /* ADD.L Dx,Ay */
  s32 a,b,s;
  a = reg68.d[reg0]<<0;
  b = reg68.a[reg9];
  ADDAL(s,a,b);
  reg68.a[reg9] = s;
}

void lineD39(u32 reg9, u32 reg0)
{
  /* ADD.L Ax,Ay */
  s32 a,b,s;
  a = reg68.a[reg0]<<0;
  b = reg68.a[reg9];
  ADDAL(s,a,b);
  reg68.a[reg9] = s;
}

void lineD3A(u32 reg9, u32 reg0)
{
  /* ADD.L <Ae>,An */
  s32 a,b,s;
  u32 addr;
  addr = get_eal[2](reg0);
  a = read_L(addr)<<0;
  b = reg68.a[reg9];
  ADDAL(s,a,b);
  reg68.a[reg9] = s;
}

void lineD3B(u32 reg9, u32 reg0)
{
  /* ADD.L <Ae>,An */
  s32 a,b,s;
  u32 addr;
  addr = get_eal[3](reg0);
  a = read_L(addr)<<0;
  b = reg68.a[reg9];
  ADDAL(s,a,b);
  reg68.a[reg9] = s;
}

void lineD3C(u32 reg9, u32 reg0)
{
  /* ADD.L <Ae>,An */
  s32 a,b,s;
  u32 addr;
  addr = get_eal[4](reg0);
  a = read_L(addr)<<0;
  b = reg68.a[reg9];
  ADDAL(s,a,b);
  reg68.a[reg9] = s;
}

void lineD3D(u32 reg9, u32 reg0)
{
  /* ADD.L <Ae>,An */
  s32 a,b,s;
  u32 addr;
  addr = get_eal[5](reg0);
  a = read_L(addr)<<0;
  b = reg68.a[reg9];
  ADDAL(s,a,b);
  reg68.a[reg9] = s;
}

void lineD3E(u32 reg9, u32 reg0)
{
  /* ADD.L <Ae>,An */
  s32 a,b,s;
  u32 addr;
  addr = get_eal[6](reg0);
  a = read_L(addr)<<0;
  b = reg68.a[reg9];
  ADDAL(s,a,b);
  reg68.a[reg9] = s;
}

void lineD3F(u32 reg9, u32 reg0)
{
  /* ADD.L <Ae>,An */
  s32 a,b,s;
  u32 addr;
  addr = get_eal[7](reg0);
  a = read_L(addr)<<0;
  b = reg68.a[reg9];
  ADDAL(s,a,b);
  reg68.a[reg9] = s;
}

static void ASR_mem(u32 reg, u32 mode)
{
  s32 a;
  u32 addr,dec;
  dec=1;
  addr = get_eaw[mode](reg);
  a = read_W(addr)<<16;
  ASRW(a,dec);
  write_W(addr,a>>16);
}

static void LSR_mem(u32 reg, u32 mode)
{
  u32 a;
  u32 addr,dec;
  dec=1;
  addr = get_eaw[mode](reg);
  a = read_W(addr)<<16;
  LSRW(a,dec);
  write_W(addr,a>>16);
}

static void ROXR_mem(u32 reg, u32 mode)
{
  u32 a;
  u32 addr,dec;
  dec=1;
  addr = get_eaw[mode](reg);
  a = read_W(addr)<<16;
  ROXRW(a,dec);
  write_W(addr,a>>16);
}

static void ROR_mem(u32 reg, u32 mode)
{
  u32 a;
  u32 addr,dec;
  dec=1;
  addr = get_eaw[mode](reg);
  a = read_W(addr)<<16;
  RORW(a,dec);
  write_W(addr,a>>16);
}

static void ASL_mem(u32 reg, u32 mode)
{
  s32 a;
  u32 addr,dec;
  dec=1;
  addr = get_eaw[mode](reg);
  a = read_W(addr)<<16;
  ASLW(a,dec);
  write_W(addr,a>>16);
}

static void LSL_mem(u32 reg, u32 mode)
{
  u32 a;
  u32 addr,dec;
  dec=1;
  addr = get_eaw[mode](reg);
  a = read_W(addr)<<16;
  LSLW(a,dec);
  write_W(addr,a>>16);
}

static void ROXL_mem(u32 reg, u32 mode)
{
  u32 a;
  u32 addr,dec;
  dec=1;
  addr = get_eaw[mode](reg);
  a = read_W(addr)<<16;
  ROXLW(a,dec);
  write_W(addr,a>>16);
}

static void ROL_mem(u32 reg, u32 mode)
{
  u32 a;
  u32 addr,dec;
  dec=1;
  addr = get_eaw[mode](reg);
  a = read_W(addr)<<16;
  ROLW(a,dec);
  write_W(addr,a>>16);
}

static void (*lslmemR_fc[4])(u32 , u32 ) =
{
  ASR_mem,  LSR_mem,  ROXR_mem,  ROR_mem,
};

static void (*lslmemL_fc[4])(u32 , u32 ) =
{
  ASL_mem,  LSL_mem,  ROXL_mem,  ROL_mem,
};

void lineE00(u32 dec, u32 reg)
{
  s32 a;
  u32 d;
  a=reg68.d[reg]<<24;
  d = ((dec-1)&7)+1;
  ASRB(a,d);
  reg68.d[reg] = (reg68.d[reg]&0xffffff00) + ((u32)a>>24);
}

void lineE01(u32 dec, u32 reg)
{
  u32 a;
  u32 d;
  a=reg68.d[reg]<<24;
  d = ((dec-1)&7)+1;
  LSRB(a,d);
  reg68.d[reg] = (reg68.d[reg]&0xffffff00) + ((u32)a>>24);
}

void lineE02(u32 dec, u32 reg)
{
  u32 a;
  u32 d;
  a=reg68.d[reg]<<24;
  d = ((dec-1)&7)+1;
  ROXRB(a,d);
  reg68.d[reg] = (reg68.d[reg]&0xffffff00) + ((u32)a>>24);
}

void lineE03(u32 dec, u32 reg)
{
  u32 a;
  u32 d;
  a=reg68.d[reg]<<24;
  d = ((dec-1)&7)+1;
  RORB(a,d);
  reg68.d[reg] = (reg68.d[reg]&0xffffff00) + ((u32)a>>24);
}

void lineE04(u32 dec, u32 reg)
{
  s32 a;
  u32 d;
  a=reg68.d[reg]<<24;
  d=reg68.d[dec]&63;
  ASRB(a,d);
  reg68.d[reg] = (reg68.d[reg]&0xffffff00) + ((u32)a>>24);
}

void lineE05(u32 dec, u32 reg)
{
  u32 a;
  u32 d;
  a=reg68.d[reg]<<24;
  d=reg68.d[dec]&63;
  LSRB(a,d);
  reg68.d[reg] = (reg68.d[reg]&0xffffff00) + ((u32)a>>24);
}

void lineE06(u32 dec, u32 reg)
{
  u32 a;
  u32 d;
  a=reg68.d[reg]<<24;
  d=reg68.d[dec]&63;
  ROXRB(a,d);
  reg68.d[reg] = (reg68.d[reg]&0xffffff00) + ((u32)a>>24);
}

void lineE07(u32 dec, u32 reg)
{
  u32 a;
  u32 d;
  a=reg68.d[reg]<<24;
  d=reg68.d[dec]&63;
  RORB(a,d);
  reg68.d[reg] = (reg68.d[reg]&0xffffff00) + ((u32)a>>24);
}

void lineE08(u32 dec, u32 reg)
{
  s32 a;
  u32 d;
  a=reg68.d[reg]<<16;
  d = ((dec-1)&7)+1;
  ASRW(a,d);
  reg68.d[reg] = (reg68.d[reg]&0xffff0000) + ((u32)a>>16);
}

void lineE09(u32 dec, u32 reg)
{
  u32 a;
  u32 d;
  a=reg68.d[reg]<<16;
  d = ((dec-1)&7)+1;
  LSRW(a,d);
  reg68.d[reg] = (reg68.d[reg]&0xffff0000) + ((u32)a>>16);
}

void lineE0A(u32 dec, u32 reg)
{
  u32 a;
  u32 d;
  a=reg68.d[reg]<<16;
  d = ((dec-1)&7)+1;
  ROXRW(a,d);
  reg68.d[reg] = (reg68.d[reg]&0xffff0000) + ((u32)a>>16);
}

void lineE0B(u32 dec, u32 reg)
{
  u32 a;
  u32 d;
  a=reg68.d[reg]<<16;
  d = ((dec-1)&7)+1;
  RORW(a,d);
  reg68.d[reg] = (reg68.d[reg]&0xffff0000) + ((u32)a>>16);
}

void lineE0C(u32 dec, u32 reg)
{
  s32 a;
  u32 d;
  a=reg68.d[reg]<<16;
  d=reg68.d[dec]&63;
  ASRW(a,d);
  reg68.d[reg] = (reg68.d[reg]&0xffff0000) + ((u32)a>>16);
}

void lineE0D(u32 dec, u32 reg)
{
  u32 a;
  u32 d;
  a=reg68.d[reg]<<16;
  d=reg68.d[dec]&63;
  LSRW(a,d);
  reg68.d[reg] = (reg68.d[reg]&0xffff0000) + ((u32)a>>16);
}

void lineE0E(u32 dec, u32 reg)
{
  u32 a;
  u32 d;
  a=reg68.d[reg]<<16;
  d=reg68.d[dec]&63;
  ROXRW(a,d);
  reg68.d[reg] = (reg68.d[reg]&0xffff0000) + ((u32)a>>16);
}

void lineE0F(u32 dec, u32 reg)
{
  u32 a;
  u32 d;
  a=reg68.d[reg]<<16;
  d=reg68.d[dec]&63;
  RORW(a,d);
  reg68.d[reg] = (reg68.d[reg]&0xffff0000) + ((u32)a>>16);
}

void lineE10(u32 dec, u32 reg)
{
  s32 a;
  u32 d;
  a=reg68.d[reg]<<0;
  d = ((dec-1)&7)+1;
  ASRL(a,d);
  reg68.d[reg] = (reg68.d[reg]&0) + ((u32)a>>0);
}

void lineE11(u32 dec, u32 reg)
{
  u32 a;
  u32 d;
  a=reg68.d[reg]<<0;
  d = ((dec-1)&7)+1;
  LSRL(a,d);
  reg68.d[reg] = (reg68.d[reg]&0) + ((u32)a>>0);
}

void lineE12(u32 dec, u32 reg)
{
  u32 a;
  u32 d;
  a=reg68.d[reg]<<0;
  d = ((dec-1)&7)+1;
  ROXRL(a,d);
  reg68.d[reg] = (reg68.d[reg]&0) + ((u32)a>>0);
}

void lineE13(u32 dec, u32 reg)
{
  u32 a;
  u32 d;
  a=reg68.d[reg]<<0;
  d = ((dec-1)&7)+1;
  RORL(a,d);
  reg68.d[reg] = (reg68.d[reg]&0) + ((u32)a>>0);
}

void lineE14(u32 dec, u32 reg)
{
  s32 a;
  u32 d;
  a=reg68.d[reg]<<0;
  d=reg68.d[dec]&63;
  ASRL(a,d);
  reg68.d[reg] = (reg68.d[reg]&0) + ((u32)a>>0);
}

void lineE15(u32 dec, u32 reg)
{
  u32 a;
  u32 d;
  a=reg68.d[reg]<<0;
  d=reg68.d[dec]&63;
  LSRL(a,d);
  reg68.d[reg] = (reg68.d[reg]&0) + ((u32)a>>0);
}

void lineE16(u32 dec, u32 reg)
{
  u32 a;
  u32 d;
  a=reg68.d[reg]<<0;
  d=reg68.d[dec]&63;
  ROXRL(a,d);
  reg68.d[reg] = (reg68.d[reg]&0) + ((u32)a>>0);
}

void lineE17(u32 dec, u32 reg)
{
  u32 a;
  u32 d;
  a=reg68.d[reg]<<0;
  d=reg68.d[dec]&63;
  RORL(a,d);
  reg68.d[reg] = (reg68.d[reg]&0) + ((u32)a>>0);
}

void lineE18(u32 dec, u32 reg)
{
  (lslmemR_fc[dec&3])(reg,0);
}

void lineE19(u32 dec, u32 reg)
{
  (lslmemR_fc[dec&3])(reg,1);
}

void lineE1A(u32 dec, u32 reg)
{
  (lslmemR_fc[dec&3])(reg,2);
}

void lineE1B(u32 dec, u32 reg)
{
  (lslmemR_fc[dec&3])(reg,3);
}

void lineE1C(u32 dec, u32 reg)
{
  (lslmemR_fc[dec&3])(reg,4);
}

void lineE1D(u32 dec, u32 reg)
{
  (lslmemR_fc[dec&3])(reg,5);
}

void lineE1E(u32 dec, u32 reg)
{
  (lslmemR_fc[dec&3])(reg,6);
}

void lineE1F(u32 dec, u32 reg)
{
  (lslmemR_fc[dec&3])(reg,7);
}

void lineE20(u32 dec, u32 reg)
{
  s32 a;
  u32 d;
  a=reg68.d[reg]<<24;
  d = ((dec-1)&7)+1;
  ASLB(a,d);
  reg68.d[reg] = (reg68.d[reg]&0xffffff00) + ((u32)a>>24);
}

void lineE21(u32 dec, u32 reg)
{
  u32 a;
  u32 d;
  a=reg68.d[reg]<<24;
  d = ((dec-1)&7)+1;
  LSLB(a,d);
  reg68.d[reg] = (reg68.d[reg]&0xffffff00) + ((u32)a>>24);
}

void lineE22(u32 dec, u32 reg)
{
  u32 a;
  u32 d;
  a=reg68.d[reg]<<24;
  d = ((dec-1)&7)+1;
  ROXLB(a,d);
  reg68.d[reg] = (reg68.d[reg]&0xffffff00) + ((u32)a>>24);
}

void lineE23(u32 dec, u32 reg)
{
  u32 a;
  u32 d;
  a=reg68.d[reg]<<24;
  d = ((dec-1)&7)+1;
  ROLB(a,d);
  reg68.d[reg] = (reg68.d[reg]&0xffffff00) + ((u32)a>>24);
}

void lineE24(u32 dec, u32 reg)
{
  s32 a;
  u32 d;
  a=reg68.d[reg]<<24;
  d=reg68.d[dec]&63;
  ASLB(a,d);
  reg68.d[reg] = (reg68.d[reg]&0xffffff00) + ((u32)a>>24);
}

void lineE25(u32 dec, u32 reg)
{
  u32 a;
  u32 d;
  a=reg68.d[reg]<<24;
  d=reg68.d[dec]&63;
  LSLB(a,d);
  reg68.d[reg] = (reg68.d[reg]&0xffffff00) + ((u32)a>>24);
}

void lineE26(u32 dec, u32 reg)
{
  u32 a;
  u32 d;
  a=reg68.d[reg]<<24;
  d=reg68.d[dec]&63;
  ROXLB(a,d);
  reg68.d[reg] = (reg68.d[reg]&0xffffff00) + ((u32)a>>24);
}

void lineE27(u32 dec, u32 reg)
{
  u32 a;
  u32 d;
  a=reg68.d[reg]<<24;
  d=reg68.d[dec]&63;
  ROLB(a,d);
  reg68.d[reg] = (reg68.d[reg]&0xffffff00) + ((u32)a>>24);
}

void lineE28(u32 dec, u32 reg)
{
  s32 a;
  u32 d;
  a=reg68.d[reg]<<16;
  d = ((dec-1)&7)+1;
  ASLW(a,d);
  reg68.d[reg] = (reg68.d[reg]&0xffff0000) + ((u32)a>>16);
}

void lineE29(u32 dec, u32 reg)
{
  u32 a;
  u32 d;
  a=reg68.d[reg]<<16;
  d = ((dec-1)&7)+1;
  LSLW(a,d);
  reg68.d[reg] = (reg68.d[reg]&0xffff0000) + ((u32)a>>16);
}

void lineE2A(u32 dec, u32 reg)
{
  u32 a;
  u32 d;
  a=reg68.d[reg]<<16;
  d = ((dec-1)&7)+1;
  ROXLW(a,d);
  reg68.d[reg] = (reg68.d[reg]&0xffff0000) + ((u32)a>>16);
}

void lineE2B(u32 dec, u32 reg)
{
  u32 a;
  u32 d;
  a=reg68.d[reg]<<16;
  d = ((dec-1)&7)+1;
  ROLW(a,d);
  reg68.d[reg] = (reg68.d[reg]&0xffff0000) + ((u32)a>>16);
}

void lineE2C(u32 dec, u32 reg)
{
  s32 a;
  u32 d;
  a=reg68.d[reg]<<16;
  d=reg68.d[dec]&63;
  ASLW(a,d);
  reg68.d[reg] = (reg68.d[reg]&0xffff0000) + ((u32)a>>16);
}

void lineE2D(u32 dec, u32 reg)
{
  u32 a;
  u32 d;
  a=reg68.d[reg]<<16;
  d=reg68.d[dec]&63;
  LSLW(a,d);
  reg68.d[reg] = (reg68.d[reg]&0xffff0000) + ((u32)a>>16);
}

void lineE2E(u32 dec, u32 reg)
{
  u32 a;
  u32 d;
  a=reg68.d[reg]<<16;
  d=reg68.d[dec]&63;
  ROXLW(a,d);
  reg68.d[reg] = (reg68.d[reg]&0xffff0000) + ((u32)a>>16);
}

void lineE2F(u32 dec, u32 reg)
{
  u32 a;
  u32 d;
  a=reg68.d[reg]<<16;
  d=reg68.d[dec]&63;
  ROLW(a,d);
  reg68.d[reg] = (reg68.d[reg]&0xffff0000) + ((u32)a>>16);
}

void lineE30(u32 dec, u32 reg)
{
  s32 a;
  u32 d;
  a=reg68.d[reg]<<0;
  d = ((dec-1)&7)+1;
  ASLL(a,d);
  reg68.d[reg] = (reg68.d[reg]&0) + ((u32)a>>0);
}

void lineE31(u32 dec, u32 reg)
{
  u32 a;
  u32 d;
  a=reg68.d[reg]<<0;
  d = ((dec-1)&7)+1;
  LSLL(a,d);
  reg68.d[reg] = (reg68.d[reg]&0) + ((u32)a>>0);
}

void lineE32(u32 dec, u32 reg)
{
  u32 a;
  u32 d;
  a=reg68.d[reg]<<0;
  d = ((dec-1)&7)+1;
  ROXLL(a,d);
  reg68.d[reg] = (reg68.d[reg]&0) + ((u32)a>>0);
}

void lineE33(u32 dec, u32 reg)
{
  u32 a;
  u32 d;
  a=reg68.d[reg]<<0;
  d = ((dec-1)&7)+1;
  ROLL(a,d);
  reg68.d[reg] = (reg68.d[reg]&0) + ((u32)a>>0);
}

void lineE34(u32 dec, u32 reg)
{
  s32 a;
  u32 d;
  a=reg68.d[reg]<<0;
  d=reg68.d[dec]&63;
  ASLL(a,d);
  reg68.d[reg] = (reg68.d[reg]&0) + ((u32)a>>0);
}

void lineE35(u32 dec, u32 reg)
{
  u32 a;
  u32 d;
  a=reg68.d[reg]<<0;
  d=reg68.d[dec]&63;
  LSLL(a,d);
  reg68.d[reg] = (reg68.d[reg]&0) + ((u32)a>>0);
}

void lineE36(u32 dec, u32 reg)
{
  u32 a;
  u32 d;
  a=reg68.d[reg]<<0;
  d=reg68.d[dec]&63;
  ROXLL(a,d);
  reg68.d[reg] = (reg68.d[reg]&0) + ((u32)a>>0);
}

void lineE37(u32 dec, u32 reg)
{
  u32 a;
  u32 d;
  a=reg68.d[reg]<<0;
  d=reg68.d[dec]&63;
  ROLL(a,d);
  reg68.d[reg] = (reg68.d[reg]&0) + ((u32)a>>0);
}

void lineE38(u32 dec, u32 reg)
{
  (lslmemL_fc[dec&3])(reg,0);
}

void lineE39(u32 dec, u32 reg)
{
  (lslmemL_fc[dec&3])(reg,1);
}

void lineE3A(u32 dec, u32 reg)
{
  (lslmemL_fc[dec&3])(reg,2);
}

void lineE3B(u32 dec, u32 reg)
{
  (lslmemL_fc[dec&3])(reg,3);
}

void lineE3C(u32 dec, u32 reg)
{
  (lslmemL_fc[dec&3])(reg,4);
}

void lineE3D(u32 dec, u32 reg)
{
  (lslmemL_fc[dec&3])(reg,5);
}

void lineE3E(u32 dec, u32 reg)
{
  (lslmemL_fc[dec&3])(reg,6);
}

void lineE3F(u32 dec, u32 reg)
{
  (lslmemL_fc[dec&3])(reg,7);
}

void lineF00(u32 reg9, u32 reg0)
{
  LINEF;
}
