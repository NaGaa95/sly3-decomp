// Reference algorithm: src/hand/func_00175090.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VirtualEntry { short delta,reserved; void (*call)(void *); }; void func_00238978(void *); char *func_00238690(void *,int); void func_001DA7D8(char *p) { char *object; struct VirtualEntry *table; func_00238978(p); object=func_00238690(*(char **)(p+0x10)+0x29C,0xC9); *(int *)(object+0x3C)=2; table=*(struct VirtualEntry **)(object+0xC); table[8].call(object+table[8].delta); }
