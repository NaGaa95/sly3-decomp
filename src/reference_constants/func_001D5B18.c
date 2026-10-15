// Reference algorithm: src/hand/func_001DA808.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_001D69D8(void *); void func_001D6820(void *,int,void *);
void func_0023C580(void *p); void func_001D5B18(char *p) { func_0023C580(p); func_001D69D8(p); func_001D6820(p, *(int *)(p + 0x16C), p + 0x1AC); func_001D6820(p, *(int *)(p + 0x190), p + 0x1B0); }
