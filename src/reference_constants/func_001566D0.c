// Reference algorithm: src/hand/func_001DE5A8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VirtualEntry { short delta,reserved; int (*query)(void *); }; int func_001566D0(char *p) { struct VirtualEntry *table = *(struct VirtualEntry **)(p + 0xC); return (unsigned)(table[100].query(p + table[100].delta) - 5) < 2; }
