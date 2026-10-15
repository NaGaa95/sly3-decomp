// Reference algorithm: src/hand/func_00149358.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_00252E40(void *,int);
void func_00238970(void *p); void func_0018B6C0(char *p) { func_00238970(p); func_00252E40(*(void **)(p + 0x10), 0x40); *(int *)(p + 0x34) = -1; *(int *)(p + 0x3C) = -1; *(int *)(p + 0x48) = -1; }
