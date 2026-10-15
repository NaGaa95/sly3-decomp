// Reference algorithm: src/hand/func_00146EE0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void D_0011A8D8(void *); void func_002BA070(void *,void *,void (*)(void *));
void func_002BA028(void *p, void *context);
void func_0011A8E0(char *p, void *context) { func_002BA028(p, context); func_002BA070(p + 0x34, p, D_0011A8D8); }
