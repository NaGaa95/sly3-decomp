// Reference algorithm: src/hand/func_001E77B0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_001BCFF8(void *,void *,float *,int,int,float); float func_001BB830(void **p,float parameter) { float result; func_001BCFF8(*p, p, &result, 0, 0, parameter); return result; }
