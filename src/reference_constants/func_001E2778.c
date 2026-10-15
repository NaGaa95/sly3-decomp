// Reference algorithm: src/hand/func_002079A0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern char D_0036C700[]; void func_001854C8(void *,int,void *); void func_001E2778(char *p,int value) { *(int *)(p+0x1400)=value; func_001854C8(D_0036C700,0x4D,p); *(int *)(p+0x1400)=-1; }
