// Reference algorithm: src/hand/func_001D00D0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI))); extern qword D_00317560; void func_0027E2E8(void *,void *); void func_00195168(char *p,void *target,float value) { *(qword *)(p + 0x90) = D_00317560; *(float *)(p + 0x9C) = value; func_0027E2E8(target, p + 0x90); }
