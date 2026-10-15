// Reference algorithm: src/hand/func_001B0808.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern char D_0036C700[],D_00375290[]; extern int D_00349F90; void func_00184968(void *); void func_001CF058(void *,int,int); void func_001CE8B0(void) { func_00184968(D_0036C700); D_00349F90 = -1; func_001CF058(D_00375290, 0, 0); }
