// Reference algorithm: src/hand/func_0014D8D8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_001F4438(char *p,int value) { int limit = *(int *)(p + 0x178); *(int *)(p + 0x17C) = 0; if(value < limit) limit = value; if(limit <= 0) limit = 0; *(int *)(p + 0x174) = limit; }
