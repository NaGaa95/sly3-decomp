// Reference algorithm: src/hand/func_001CF5D0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_0021DD58(void *,int); void func_001A99D0(void *,void *); void func_001D2D48(char *p,int enabled) { func_0021DD58(p, enabled); if(enabled) func_001A99D0(p + 0x204, *(void **)(p + 0x1C)); }
