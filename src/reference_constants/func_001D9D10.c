// Reference algorithm: src/hand/func_00179A58.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI))); extern qword D_00317560; void func_001D9EF0(void *,int,qword); void func_00252FC0(void *,int);
void func_00238980(void *p); void func_001D9D10(char *p) { func_00238980(p); func_001D9EF0(p, -1, D_00317560); func_00252FC0(*(void **)(p + 0x10), 0x3E); }
