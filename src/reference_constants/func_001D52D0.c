// Reference algorithm: src/hand/func_001D7780.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern char D_0046F550[],D_00345CA0[]; void func_001D3818(void *,int,void *); void func_001D52D0(char *p) { func_001D3818(D_0046F550,2,D_00345CA0); if(p)*(int *)(p+0x1C)|=2; }
