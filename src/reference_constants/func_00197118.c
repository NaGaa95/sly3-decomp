// Reference algorithm: src/hand/func_001709A8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
int func_0013B500(void *p, int n);
int func_00197118(void *p) { if (func_0013B500(p, 0xC)) return 0; if (func_0013B500(p, 0xA)) return 1; return -1; }
