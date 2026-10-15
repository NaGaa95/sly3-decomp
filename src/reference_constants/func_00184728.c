// Reference algorithm: src/hand/func_0020FA50.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VirtualEntry { short adjustment; short reserved; void (*call)(void *); }; void func_00184728(char *p) { if(!*(int *)(p + 0x6C)) { char *owner = *(char **)(p + 0x54); struct VirtualEntry *table = *(struct VirtualEntry **)(owner + 0xC); table[8].call(owner + table[8].adjustment); *(int *)(p + 0x6C) = 1; } }
