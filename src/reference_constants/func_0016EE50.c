// Reference algorithm: src/hand/func_0013CFD8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void *func_002B52F0(void *); void func_00117E30(void *); extern char D_003561F8[]; void *func_0016EE50(char *p) { func_002B52F0(p); *(void **)(p + 0xC) = D_003561F8; func_00117E30(p + 0x50); *(int *)(p + 0x698) = -1; return p; }
