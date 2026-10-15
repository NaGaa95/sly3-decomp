// Reference algorithm: src/hand/func_001B3190.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_00169D98(void *); void func_00169CB0(void *,int); void func_00169C40(void **p) { if(*p) { func_00169D98(*p); if(*p)func_00169CB0(*p,3); *p=0; } }
