// Reference algorithm: src/hand/func_00146EE0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_001F4DD8(void *,int,int,float);
void func_001FC968(void *p, void *context);
void func_001F3C48(char *p, void *context) { func_001FC968(p, context); func_001F4DD8(p, 0, -1, 0.0f); }
