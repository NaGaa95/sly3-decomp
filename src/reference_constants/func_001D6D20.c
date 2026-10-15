// Reference algorithm: src/hand/func_00132B78.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_0013BD88(void *,void *); void func_0013BD00(void *,void *); void func_001D6D20(char *p,void *owner) { void *old = *(void **)(p + 0x1F0); if(old) func_0013BD88(old, p); *(void **)(p + 0x1F0) = owner; if(owner) func_0013BD00(owner, p); }
