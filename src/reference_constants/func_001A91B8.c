// Reference algorithm: src/hand/func_001F0198.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_001A97B8(void *);
void func_001A91B8(char *p) { *(void **)(p + 0x110C) = 0; func_001A97B8(p); }
