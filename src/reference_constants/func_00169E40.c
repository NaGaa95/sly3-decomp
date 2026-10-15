// Reference algorithm: src/hand/func_001320C8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_001679E0(void *,float); void func_00169E40(char *p) { func_001679E0(*(void **)p,*(float *)(p+0x18)); *(float *)(*(char **)p+0x11C)=*(float *)(p+0x14); }
