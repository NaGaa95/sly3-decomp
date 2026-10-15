// Reference algorithm: src/hand/func_001C3DC8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_0024E370(void *a);
void func_001C12B0(void *b);
void func_00156438(void *a) { func_0024E370(a); func_001C12B0((char *)a + 0xA20); }
