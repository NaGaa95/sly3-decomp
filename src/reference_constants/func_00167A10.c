// Reference algorithm: src/hand/func_001A35B0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_001679E0(void *,float); void func_00167A10(char *p,float value) { char *owner; func_001679E0(p, value); owner = *(char **)(p + 0x300); if(owner) *(float *)(owner + 0x18) = value; }
