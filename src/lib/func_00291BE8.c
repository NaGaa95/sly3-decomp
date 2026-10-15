// Reference: Sly 2 src/lib/func_00232F88.c; target Sly 3 0x00291BE8.
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
int func_00291290(int, int, void *);
void func_00291BE8(int a, int b, int c, int d, int e) { int buf[5]; buf[0] = a; buf[1] = b; buf[2] = c; buf[3] = d; buf[4] = e; func_00291290(0x3E, 0x14, buf); }
