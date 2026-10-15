// Reference algorithm: src/hand/func_00146EE0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
int func_0016E8D8(void *); void func_0016E6C0(void *,int);
void func_00238978(void *p);
void func_0016E5D8(char *p) { func_00238978(p); func_0016E6C0(p, func_0016E8D8(p)); }
