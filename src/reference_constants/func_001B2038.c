// Reference algorithm: src/hand/func_00176060.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VirtualEntry { short delta,reserved; float *(*query)(void *); }; float func_002A3EE8(float,float); float func_001B2038(char *p) { char *owner = *(char **)(p + 0x19F4); struct VirtualEntry *table = *(struct VirtualEntry **)(owner + 0xC); float *vector = table[36].query(owner + table[36].delta); return func_002A3EE8(vector[1], vector[0]); }
