// Reference algorithm: src/hand/FUN_0018d328.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VirtualEntry { short delta,reserved; void (*call)(void *); }; int func_0011B0C0(void *,void *); void func_0011AF60(void *,void *); void func_0015B5E0(char *p,char *object) { void *list=p+0x3E90; if(!func_0011B0C0(list,object)) { struct VirtualEntry *table; func_0011AF60(list,object); table=*(struct VirtualEntry **)(object+0x14); table[2].call(object+table[2].delta); } }
