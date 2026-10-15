// Reference algorithm: src/hand/func_001C3DC8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_001FC8F8(void *a, void *b);
void func_00118420(void *b);
void func_00184520(char *a, void *b) { func_001FC8F8(a, b); *(int *)(a + 0x70) = 0; *(int *)(a + 0x74) = 0; }
