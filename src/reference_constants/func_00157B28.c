// Reference algorithm: src/hand/func_001F3868.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
void func_00238978(void *);
void func_001F4E20(void *);
void func_001586C0(void *, int);
void func_00157B28(void *p) { func_00238978(p); func_001F4E20(*(void **)(*(char **)((char *)p + 0x10) + 0x140)); func_001586C0(p, 0); }
