// Reference algorithm: src/hand/func_001F0198.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_00186EE0(void *, int, int, int);
void func_00186E80(void *p, int value) { func_00186EE0(p, value, -1, -1); }
