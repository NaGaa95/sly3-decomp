// Reference algorithm: src/hand/func_001F0198.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_001E8E60(void *, int);
void func_001E8E40(char *p, void *owner) { *(void **)(p + 0x190) = owner; func_001E8E60(p, 0); }
