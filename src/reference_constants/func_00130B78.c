// Reference algorithm: src/hand/func_001DB7A8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI))); extern qword D_00317530,D_00317550;
void func_0028FD70(void *p); void func_00130B78(char *p) { func_0028FD70(p); *(qword *)(p + 0xF0) = D_00317530; *(qword *)(p + 0x100) = D_00317550; }
