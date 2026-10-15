// Reference algorithm: src/hand/func_001B34D0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_001FDFD0(void *,int); int func_001FE158(char *p,int command) { if(command == 1) func_001FDFD0(p, 2); return *(int *)(*(char **)(p + 0x20) + 0x1C); }
