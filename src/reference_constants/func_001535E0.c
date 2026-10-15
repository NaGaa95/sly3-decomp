// Reference algorithm: src/hand/func_00184380.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern char D_0036C700[]; void func_001854C8(void *,int,void *); void func_001535E0(char *p) { if(!*(int *)(p+0xE68)) { *(int *)(p+0xE68)=1; func_001854C8(D_0036C700,0xC,p); } }
