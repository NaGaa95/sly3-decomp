// Reference: Sly 2 src/lib/func_00235100.c; target Sly 3 0x00293D80.
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
int func_00293D80(void) { int s; __asm__ volatile("mfc0 %0, $12" : "=r"(s)); return (s ^ 1) & 1; }
