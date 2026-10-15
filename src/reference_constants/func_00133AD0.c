// Reference algorithm: src/hand/func_0014B1A0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_00133EC0(void *,int,int);
void func_00238978(void *p);
void func_00133AD0(char *p) { func_00238978(p); func_00133EC0(p, *(int *)(p + 0x3C), 0); }
