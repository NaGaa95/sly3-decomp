// Reference algorithm: src/hand/func_00161958.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VirtualEntry { short delta,reserved; void (*call)(void *); }; void func_00257EC8(void *,int); void func_00133E78(char *p) { char *owner = *(char **)(p + 0x10); struct VirtualEntry *table = *(struct VirtualEntry **)(owner + 0xC); table[9].call(owner + table[9].delta); func_00257EC8(*(void **)(p + 0x10), 0); }
