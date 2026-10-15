// Reference algorithm: src/hand/func_00146EE0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_001EE220(void *,void *); void func_001E73D8(char *p) { void *owner = *(void **)(p + 0x1CC); if(owner) { func_001EE220(owner, p); *(void **)(p + 0x1CC) = 0; } }
