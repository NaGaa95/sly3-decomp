// Reference algorithm: src/hand/func_001C3DC8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_0014C7F0(void *a, void *b);
void func_001309D8(void *b);
void func_001D6D70(void *a, void *b) { func_0014C7F0(a, b); func_001309D8((char *)a + 0x248); }
