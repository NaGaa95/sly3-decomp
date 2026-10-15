// Reference algorithm: src/hand/func_002296C0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_00155F80(void *,int,void *); void func_0014DC98(void *,void *); void func_00155ED8(char *p,void *source) { if(*(void **)(p+0x127C)) { func_00155F80(p,2,0); func_0014DC98(*(void **)(p+0x127C),source); } }
