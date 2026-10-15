// Reference algorithm: src/hand/func_00224068.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VirtualEntry { short adjustment,reserved; void (*call)(void *); }; void func_00261030(void *); void func_001853D8(char *p) { char *owner = *(char **)(p + 0x42E4); if(owner) { struct VirtualEntry *table = *(struct VirtualEntry **)(owner + 0xC); table[56].call(owner + table[56].adjustment); func_00261030(owner); } }
