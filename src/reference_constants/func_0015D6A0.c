// Reference algorithm: src/hand/func_00182E80.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_0024AEF8(void *,int,int,void *); void *func_0015D6A0(void *p,char *source) { func_0024AEF8(p, *(int *)(source + 0x23C), 0x2002, *(void **)(source + 0x240)); return p; }
