// Reference algorithm: src/hand/func_00209098.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
int func_00155B88(void *); int func_001EA478(char *p) { if(*(int *)(p + 0x16A8) != -1) return 0x2000; else return func_00155B88(p); }
