// Reference: Sly 2 src/lib/_sceMpegStopIpuDma.c; target Sly 3 0x002AE2F8.
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
int func_002980D0(void);
int func_00298120(void);
#define REG(a) (*(volatile unsigned int *)(a))
void _sceMpegStopIpuDma(void)
{
  int s = func_002980D0();
  REG(0x1000F590) = REG(0x1000F520) | 0x10000;
  REG(0x1000B000) = 0;
  REG(0x1000B400) = 0;
  REG(0x1000F590) = REG(0x1000F520) & ~0x10000;
  if (s) func_00298120();
  REG(0x1000B020) = 0;
  REG(0x1000B420) = 0;
  REG(0x10002010) = 0x40000000;
}
