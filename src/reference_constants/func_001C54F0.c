// Reference algorithm: src/hand/func_00130488.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI))); void func_001C5868(void *); void func_001C54F0(char *p,qword value) { *(qword *)(p + 0xE0) = value; func_001C5868(p); }
