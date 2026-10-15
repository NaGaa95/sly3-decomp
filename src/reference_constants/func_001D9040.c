// Reference algorithm: src/hand/func_00224028.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI))); void func_001573A0(void *); void func_001572A0(void *,qword);
void func_001D8070(void *p);
void func_001D9040(char *p) { func_001D8070(p); func_001573A0(*(char **)(p + 0x10) + 0x10A0); func_001572A0(*(char **)(p + 0x10) + 0x10A0, *(qword *)(p + 0x60)); }
