// Reference algorithm: src/hand/func_002292D8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
int func_00260738(void *); int func_00163738(char *p) { void *owner = *(void **)(p + 0x194); if(!owner) return 1; else return func_00260738(owner); }
