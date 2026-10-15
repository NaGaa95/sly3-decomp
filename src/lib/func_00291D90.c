// Reference: Sly 2 src/lib/func_00233130.c; target Sly 3 0x00291D90.
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
void func_002914C0(int, int, void *, int, int);
void func_00291D90(int a, int b, int c, int d, int e, int f) { int buf[4]; buf[0] = a; buf[1] = b; buf[2] = c; buf[3] = d; func_002914C0(0x68, c + 0xC, buf, e, f); }
