// Reference algorithm: src/hand/func_00132100.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern char D_003468A0[]; void func_001C8970(void *,int,void *,void *);
void func_00152448(void *p, void *stream);
void func_001EFF30(char *p, void *stream) { func_00152448(p, stream); func_001C8970(p, 0x35, D_003468A0, 0); }
