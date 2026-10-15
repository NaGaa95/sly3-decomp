// Reference: Sly 2 src/lib/func_00232FE8.c; target Sly 3 0x00291C48.
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
int func_00291290(int, int, void *);
void func_00291C48(int a, int b) { int buf[2]; buf[0] = a; buf[1] = b; func_00291290(0x5A, 8, buf); }
