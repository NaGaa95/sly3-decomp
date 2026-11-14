// Sly 2 counterpart: sceMpegInit (decomp src/lib/sceMpegInit.c)
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
int func_002980D0(void);
int func_00298120(void);
void func_002B36D0(void);
#define REG(a) (*(volatile unsigned int *)(a))
int func_002A9EA8(void)
{
  int s = func_002980D0();
  REG(0x1000F590) = REG(0x1000F520) | 0x10000;
  REG(0x1000B000) = REG(0x1000B000) & ~0x100;
  REG(0x1000B400) = REG(0x1000B400) & ~0x100;
  REG(0x1000F590) = REG(0x1000F520) & ~0x10000;
  if (s) func_00298120();
  REG(0x1000B020) = 0;
  REG(0x1000B420) = 0;
  func_002B36D0();
  return 1;
}
