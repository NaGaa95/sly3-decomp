// Reference algorithm: src/hand/func_00146EE0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_001F4DD8(void *,int,int,float);
void func_001FCB20(void *p);
void func_001F3C80(char *p) { func_001FCB20(p); func_001F4DD8(p, 0, -1, 0.0f); }
