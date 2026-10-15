// Reference algorithm: src/hand/func_00130488.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
int func_001EB4C8(void *);
int func_001ED170(char *p) { return func_001EB4C8(p + 0xD0) != 0; }
