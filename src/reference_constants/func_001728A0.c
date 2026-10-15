// Reference algorithm: src/hand/func_0014D1D0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct X { char pad[0x18]; float af[4]; };
void func_001727F8(void *p, int mode, int value, int limit);
void func_001728A0(void *p, int value) { func_001727F8(p, 1, value, -1); }
