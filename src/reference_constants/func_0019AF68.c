// Reference algorithm: src/hand/func_002292D8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
int func_001A29B0(void *); int func_0019AF68(char *p) { void *owner = *(void **)(*(char **)(p + 0x10) + 0x11C8); if(!owner) return 0; return func_001A29B0(owner) != 0; }
