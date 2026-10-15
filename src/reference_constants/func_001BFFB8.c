// Reference algorithm: src/hand/func_001F5860.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void *func_001BFFB8(char *p,int kind) { if(kind == 3) return *(void **)(*(char **)p + 0x13E0); return 0; }
