// Reference algorithm: src/hand/func_00133E30.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VirtualEntry { short delta,reserved; void (*call)(void *); }; void func_00184778(char *p) { if(*(int *)(p+0x6C)) { char *object=*(char **)(p+0x54); struct VirtualEntry *table=*(struct VirtualEntry **)(object+0xC); table[9].call(object+table[9].delta); *(int *)(p+0x6C)=0; } }
