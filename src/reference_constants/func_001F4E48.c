// Reference algorithm: src/hand/func_00119C08.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_001F4EC0(void *); void func_001F4E48(char *p) { *(int *)(p + 8) += -1; func_001F4EC0(p); }
