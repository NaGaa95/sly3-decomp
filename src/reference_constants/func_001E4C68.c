// Reference algorithm: src/hand/func_001DA808.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_00240E58(void *,int,int);
void func_0023AE08(void *p); void func_001E4C68(char *p) { func_0023AE08(p); func_00240E58(p, 0x3FFFFFF, 2); func_00240E58(p, 0x88001, 0); }
