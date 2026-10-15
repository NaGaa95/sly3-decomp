// Reference algorithm: src/hand/func_00119C08.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
int func_0011B0C0(void *,void *); int func_00169E88(void **p) { return !func_0011B0C0((char *)*p + 0x300, p); }
