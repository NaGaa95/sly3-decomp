// Reference algorithm: src/hand/func_00176060.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VirtualEntry { short delta,reserved; char *(*query)(void *); }; void *func_0013B868(char *p) { struct VirtualEntry *table=*(struct VirtualEntry **)(p+0xC); char *type=table[6].query(p+table[6].delta); return *(void **)(type+4); }
