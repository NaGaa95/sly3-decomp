// Reference algorithm: src/hand/func_00179A58.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
int func_001985F0(void *,void *); void *func_002387A8(void *,int); void func_00197838(void *,int,int,int); void func_001985A8(char *p,void *context) { if(func_001985F0(p, context)) func_00197838(func_002387A8(p + 0x29C, 0xD3), 0, 0, 0); }
