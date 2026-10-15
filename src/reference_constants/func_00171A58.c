// Reference algorithm: src/hand/func_0015C150.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern char D_00344898[],D_00321130[]; void *func_0021CCD0(void *,void *); void func_00171A58(char *p) { *(void **)(p+0x14)=D_00344898; *(void **)(p+8)=func_0021CCD0(D_00321130,0); *(int *)(p+0x10)=1; }
