// Reference algorithm: src/hand/func_00171F58.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern float D_0036BB98; void func_0015F050(void *,int); void func_00251A58(void *,int);
void func_00238978(void *p);
void func_0015E3D0(char *p) { func_00238978(p); func_0015F050(p, 0); *(float *)(p + 0x48) = D_0036BB98; func_00251A58(*(void **)(p + 0x10), 0); }
