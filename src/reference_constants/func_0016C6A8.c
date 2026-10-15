// Reference algorithm: src/hand/func_001C3DC8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_00169E40(void *a);
void func_00166548(void *b);
void func_0016C6A8(void *a) { func_00169E40(a); func_00166548(*(void **)a); }
