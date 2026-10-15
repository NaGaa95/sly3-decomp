// Reference algorithm: src/hand/func_001C2D20.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VirtualEntry { short delta,reserved; void (*call)(void *); }; extern char D_00344070[]; void func_0023C580(void *); void func_001C8970(void *,int,void *,void *); void func_00159E50(char *p) { struct VirtualEntry *table; func_0023C580(p); func_001C8970(p,2,D_00344070,0); table=*(struct VirtualEntry **)(p+0xC); table[9].call(p+table[9].delta); }
