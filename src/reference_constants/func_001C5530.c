// Reference algorithm: src/hand/func_00130488.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_001C5868(void *); void func_001C5530(char *p,float value) { *(float *)(p + 0x144) = value; func_001C5868(p); }
