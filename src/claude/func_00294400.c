// Sly 2 counterpart: kputchar (decomp src/lib/kputchar.c)
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder
int func_00294400(int c)
{
  while (*(volatile unsigned int *)0x1000F130 & 0x8000) ;
  *(volatile unsigned char *)0x1000F180 = c;
  return c;
}
