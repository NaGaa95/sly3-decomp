// Reference: Sly 2 src/lib/func_002321B8.c; target Sly 3 0x00290E68.
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
void func_002914C0(int, int, void *, int, int);
void func_00290E68(int a) { int buf[1]; buf[0] = a; func_002914C0(6, 4, buf, 0, 0); }
