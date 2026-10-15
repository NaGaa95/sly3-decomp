// Reference algorithm: src/hand/func_00227728.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_0024E400(void *,void *,void *); void func_001C3D18(void *,void *,void *); void func_001F1120(char *p,void *first,void *second) { func_0024E400(p,first,second); if(*(int *)(p+0x1470)==7)func_001C3D18(p+0xE40,first,second); }
