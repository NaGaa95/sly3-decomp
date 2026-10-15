// Reference algorithm: src/hand/func_00182E80.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0

void func_001FCEE8(void *p);
void func_001FD7B0(char *p) { func_001FCEE8(p); (*(unsigned short **)(p + 0x1C))[0x16]++; }
