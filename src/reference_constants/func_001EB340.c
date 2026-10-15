// Reference algorithm: src/hand/func_00221268.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_00261580(void *,int,float); void func_001EB340(char *p) { void *owner = *(void **)(p + 0x16FC); if (owner) func_00261580(owner, 0x37C, *(float *)(p + 0x1700)); }
