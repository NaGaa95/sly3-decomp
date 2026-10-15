// Reference algorithm: src/hand/func_001C3DC8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_0022DCC8(void *a);
void func_0015CE68(void *b);
void func_001F32B8(void *a) { func_0022DCC8(a); func_0015CE68((char *)a + 0x1A8); }
