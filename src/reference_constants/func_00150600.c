// Reference algorithm: src/hand/func_001A66C8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern void *D_002EDEE8[]; extern char D_00320410[]; void *func_00150600(int index) { if(index==-1)return D_00320410; return D_002EDEE8[index]; }
