// Reference algorithm: src/hand/func_00176708.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct F { int a[0x4]; };
void func_00238978(void *p);
void func_00292034(void *p, int c, int n);
void func_0019A2D0(void *p, struct F *pf);
void func_0019A238(void *p) { struct F f; func_00238978(p); func_00292034(&f, 0, sizeof(f)); f.a[0] = 0; func_0019A2D0(p, &f); }
