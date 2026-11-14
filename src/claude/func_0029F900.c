// Sly 2 counterpart: func_00240AA0 (decomp src/lib/func_00240AA0.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
__asm__(".macro sq r, m\n\tsd \\r, \\m\n\t.endm\n\t.macro lq r, m\n\tld \\r, \\m\n\t.endm");
int func_002939C0(int); void func_002939E0(int);
int func_0029F900(int a) { int r = func_002939C0(a); func_002939E0(a); return r; }
