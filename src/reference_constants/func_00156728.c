// Reference algorithm: src/hand/func_0017EE78.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
int func_001F4830(void *); int func_001C4018(void *); int func_00156728(char *p) { if (!func_001F4830(p)) return 0; return func_001C4018(p + 0xE40) != 2; }
