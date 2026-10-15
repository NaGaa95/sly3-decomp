// Reference algorithm: src/hand/func_001F0198.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_00186EE0(void *, int, int, int);
void func_00186EC0(void *p, int value, int selection) { func_00186EE0(p, value, -1, selection); }
