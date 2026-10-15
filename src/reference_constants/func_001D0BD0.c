// Reference algorithm: src/hand/func_001FB060.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_001D0C08(void *,int); void func_001D0BD0(char *p) { if(*(int *)(p + 0x34)) { int state = *(int *)(p + 0x50); if(state != -1) func_001D0C08(p, state); } }
