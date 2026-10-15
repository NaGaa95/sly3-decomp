// Reference algorithm: src/hand/func_001C3DC8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_001C81B8(void *a);
void func_0015CE68(void *b);
void func_001A1610(void *a) { func_001C81B8(a); func_0015CE68((char *)a + 0xF8); }
