// Reference algorithm: src/hand/func_001F5860.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void *func_00156AB0(char *p) { char *owner = *(char **)(p + 0x1140); if(owner) return *(void **)(owner + 0x30); return *(void **)(p + 0x113C); }
