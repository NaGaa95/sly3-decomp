// Reference algorithm: src/hand/func_001C3DC8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_00252508(void *a);
void func_00162678(void *b);
void func_00161CD0(void *a) { func_00252508(a); func_00162678((char *)a + 0x1884); }
