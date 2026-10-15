// Reference algorithm: src/hand/func_00146EE0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_0019C570(void *,int);
void func_0019B668(void *p);
void func_0019BE58(char *p) { func_0019B668(p); func_0019C570(p, *(int *)(p + 0x130) != -1); }
