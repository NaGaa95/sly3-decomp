// Reference algorithm: src/hand/func_001B34D0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_0024AEF8(void *,int,int,void *); void *func_0015C5D8(void *p,char *source) { func_0024AEF8(p, *(int *)(source + 0x5C), 7, source + 0x60); return p; }
