// Reference algorithm: src/hand/func_001492B0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_001825C0(void *,int,int); void func_00252FC0(void *,int);
void func_00238980(void *p); void func_00182028(char *p) { func_00238980(p); func_001825C0(p, -1, 0); func_00252FC0(*(void **)(p + 0x10), 0x2D); }
