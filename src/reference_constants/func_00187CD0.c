// Reference algorithm: src/hand/func_001A2358.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
int func_00188A38(void *); int func_00187CD0(char *p) { void *owner = *(void **)(p + 0x58); if(owner) return func_00188A38(owner) != 0; return 0; }
