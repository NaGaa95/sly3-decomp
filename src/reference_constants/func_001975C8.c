// Reference algorithm: src/hand/func_001F0198.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void *func_00197628(void *, int, int);
void *func_001975C8(void *p) { return func_00197628(p, 0x10, -1); }
