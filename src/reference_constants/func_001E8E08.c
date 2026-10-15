// Reference algorithm: src/hand/func_001E7930.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void *func_00169BF8(unsigned int); void *func_00169C90(void *,void *,int); void *func_001E8E08(void *unused,void *p) { return func_00169C90(func_00169BF8(0x20), p, 1); }
