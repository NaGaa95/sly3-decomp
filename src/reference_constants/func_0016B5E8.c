// Reference algorithm: src/hand/func_0013CFD8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void *func_00169C90(void *,void *,int); extern char D_00355CC8[]; void *func_0016B5E8(char *p,void *owner,int mode) { func_00169C90(p, owner, mode); *(void **)(p + 0x1C) = D_00355CC8; *(int *)(p + 8) = 7; *(void **)(p + 0x160) = p + 0x70; return p; }
