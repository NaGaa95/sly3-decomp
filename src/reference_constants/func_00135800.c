// Reference algorithm: src/hand/func_00132100.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_00135A50(void *,int); void func_00259D10(void *);
void func_00238978(void *p);
void func_00135800(char *p) { func_00238978(p); func_00135A50(p, 0); func_00259D10(*(char **)(p + 0x10) + 0x4B0); }
