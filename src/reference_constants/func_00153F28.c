// Reference algorithm: src/hand/func_00132100.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_00137628(void *); void func_00238568(void *);
void func_0023BBE0(void *p);
void func_00153F28(char *p) { func_0023BBE0(p); func_00137628(p + 0xF50); func_00137628(p + 0xF74); func_00238568(p + 0x29C); }
