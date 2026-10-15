// Reference algorithm: src/hand/func_001F82B8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_00152DC0(void *,int); void func_001E4A20(void *,int); void func_001DD8C0(void *p,int state) { func_00152DC0(p, state); if(state == -1) func_001E4A20(p, 0); }
