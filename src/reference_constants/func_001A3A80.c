// Reference algorithm: src/hand/func_0017DDE8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern char D_0036C700[]; void func_00238978(void *); void func_001A4800(void *,int,void *); void func_002541F8(void *,void *); void func_001854C8(void *,int,void *); void func_001A3A80(char *p) { func_00238978(p); func_001A4800(p,3,0); func_002541F8(*(void **)(p+0x10),*(void **)(p+0x30)); func_001854C8(D_0036C700,0x1C,*(void **)(p+0x10)); }
