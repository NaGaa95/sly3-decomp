// Reference algorithm: src/hand/func_001A66C8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern void *D_002EDE48[]; extern char D_00320400[]; void *func_001505D0(int index) { if(index==-1)return D_00320400; return D_002EDE48[index]; }
