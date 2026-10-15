// Reference algorithm: src/hand/func_00151648.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_001A20F8(void *,void *); int func_0013B500(void *,int); void func_001DF7E8(void *,void *); void func_001A22A8(void *p,void *object) { func_001A20F8(p, object); if(func_0013B500(object, 0x35)) func_001DF7E8(object, p); }
