// Reference algorithm: src/hand/func_00130488.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI))); void func_00169398(void *); void func_00169460(char *p,qword value) { *(qword *)(p + 0x60) = value; func_00169398(p); }
