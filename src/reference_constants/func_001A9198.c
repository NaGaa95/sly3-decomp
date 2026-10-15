// Reference algorithm: src/hand/func_00130488.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_001A97B8(void *); void func_001A9198(char *p,void *value) { *(void **)(p + 0x110C) = value; func_001A97B8(p); }
