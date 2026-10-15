// Reference algorithm: src/hand/func_001F5860.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_001F43D0(char *p,int value) { int limit = *(int *)(p + 0x170); if(value < limit) limit = value; if(limit <= 0) limit = 0; *(int *)(p + 0x16C) = limit; }
