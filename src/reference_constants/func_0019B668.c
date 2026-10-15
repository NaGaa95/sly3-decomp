// Reference algorithm: src/hand/func_0012E6A0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
int func_001F43F0(void *); void func_001F43D0(void *,int); void func_0019BB00(void *,int,int);
void func_001F3C48(void *p); void func_0019B668(char *p) { func_001F3C48(p); func_001F43D0(p, func_001F43F0(p)); func_0019BB00(p, 0, 0); }
