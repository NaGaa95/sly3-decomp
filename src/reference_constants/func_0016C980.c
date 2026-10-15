// Reference algorithm: src/hand/func_001F3868.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
void func_00238978(void *);
void func_00252E40(void *, int);
void func_0016CB38(void *, int);
void func_0016C980(void *p) { func_00238978(p); func_00252E40(*(void **)((char *)p + 0x10), *(int *)((char *)p + 0x40)); func_0016CB38(p, 0); }
