// Reference algorithm: src/hand/func_00210990.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
int func_00185FD8(char *p) { if(*(void **)(p + 0x50)) return 0; return *(int *)(p + 0xF0) != 3; }
