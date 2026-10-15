// Reference algorithm: src/hand/func_001D7780.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern char D_0046F550[]; void func_001D2D90(void *,void *); void func_001D4C48(void *); void func_001D2DF8(void *); void func_001D4BF8(void *source) { func_001D2D90(D_0046F550,source); func_001D4C48(0); if(*(int *)(D_0046F550+0x38)<=0)func_001D2DF8(D_0046F550); }
