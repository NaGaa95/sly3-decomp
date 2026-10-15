// Reference algorithm: src/hand/func_0014B1A0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_0019DC10(void *,int);
void func_0019B668(void *p);
void func_0019CED8(char *p) { func_0019B668(p); func_0019DC10(p, 0); *(int *)(p + 0x3F8) = 0; }
