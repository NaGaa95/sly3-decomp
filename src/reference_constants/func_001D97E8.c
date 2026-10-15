// Reference algorithm: src/hand/func_0016E380.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_001D9A88(void *,int); void func_00238A38(void *); void func_00252FC0(void *,int);
void func_00238980(void *p);
void func_001D97E8(char *p) { func_00238980(p); func_001D9A88(p, -1); func_00238A38(p); func_00252FC0(*(void **)(p + 0x10), 0x3D); }
