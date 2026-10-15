// Reference algorithm: src/hand/func_0017CAC8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_001679E0(void *,float);
void func_00169E28(void *p); void func_0016BF60(char *p) { func_00169E28(p); func_001679E0(*(void **)p, 49.0f); *(float *)(*(char **)p + 0x11C) = *(float *)(*(char **)(p + 0x20) + 0x1CC); }
