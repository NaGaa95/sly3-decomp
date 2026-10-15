// Reference algorithm: src/hand/func_00171F58.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_00149A08(void *,int); float func_0011E940(float,float); void func_001781B8(char *p) { *(int *)(p+0xD0)=0; if(*(void **)(p+0x12C))func_00149A08(*(void **)(p+0x12C),*(int *)(p+0xD4)); *(float *)(p+0x110)=func_0011E940(*(float *)(p+0xE8),*(float *)(p+0xEC)); }
