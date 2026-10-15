// Reference algorithm: src/hand/func_001492B0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_001FCEE8(void *); void func_001FDEE8(char *p) { char *owner; func_001FCEE8(p); owner=*(char **)(p+0x1C); ++*(unsigned short *)(owner+0x20); }
