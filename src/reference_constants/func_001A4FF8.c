// Reference algorithm: src/hand/func_001F3868.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
void func_00238980(void *);
void func_001A5038(void *, int);
void func_00252FC0(void *, int);
void func_001A4FF8(void *p) { func_00238980(p); func_001A5038(p, -1); func_00252FC0(*(void **)((char *)p + 0x10), 0x34); }
