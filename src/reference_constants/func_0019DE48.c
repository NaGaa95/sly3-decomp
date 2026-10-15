// Reference algorithm: src/hand/func_0014B1A0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_0019B968(void *,int,void *);
void func_001F3BF8(void *p);
void func_0019DE48(char *p) { func_001F3BF8(p); func_0019B968(p, 3, p + 0x200); }
