// Reference algorithm: src/hand/func_001A30D0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_00169398(void *); void func_001694A0(char *p,float value) { *(float *)(p+0x70)=value; func_00169398(p); }
