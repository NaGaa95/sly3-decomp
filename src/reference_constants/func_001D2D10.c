// Reference algorithm: src/hand/func_0014B1A0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_001D2ED0(void *,int);
void func_001D3AE8(void *p);
void func_001D2D10(char *p) { func_001D3AE8(p); func_001D2ED0(p, 0); *(int *)(p + 0x30) = 0; }
