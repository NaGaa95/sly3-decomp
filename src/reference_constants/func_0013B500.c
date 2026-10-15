// Reference algorithm: src/hand/func_001492B0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VirtualEntry { short delta,reserved; char *(*query)(void *); }; int func_0013BEC8(void *,int); int func_0013B500(char *p,int kind) { struct VirtualEntry *table = *(struct VirtualEntry **)(p + 0xC); char *type = table[6].query(p + table[6].delta); return func_0013BEC8(*(void **)(type + 4), kind); }
