// Reference algorithm: src/hand/func_00132100.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern char D_00345FB0[]; void func_001C8970(void *,int,void *,void *);
void func_0023C0B8(void *p, void *context);
void func_001D6C00(char *p, void *context) { func_0023C0B8(p, context); func_001C8970(p, 0x1, D_00345FB0, 0); }
