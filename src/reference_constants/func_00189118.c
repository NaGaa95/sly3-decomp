// Reference algorithm: src/hand/func_0014D1D0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct X { char pad[0x18]; float af[4]; };
void func_00189160(void *p, int mode);
void func_00189118(char *p) { *(int *)(p + 0x0) = -1; func_00189160(p, 0); }
