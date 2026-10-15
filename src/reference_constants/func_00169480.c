// Reference algorithm: src/hand/func_00130488.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_00169398(void *); void func_00169480(char *p,float value) { *(float *)(p + 0x74) = value; func_00169398(p); }
