// Reference: Sly 2 src/lib/func_002321E8.c; target Sly 3 0x00290E98.
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
void func_002914C0(int, int, void *, int, int);
void func_00290E98(int a, int b) { int buf[2]; buf[0] = a; buf[1] = b; func_002914C0(9, 8, buf, 0, 0); }
