// Reference algorithm: src/hand/func_00133E30.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VirtualEntry { short delta,reserved; void (*call)(void *); }; extern char D_004BC220[]; void func_0027ED18(void *); void func_001C4F70(char *p) { if(*(void **)p) { char *object; struct VirtualEntry *table; func_0027ED18(D_004BC220); object=*(char **)p; table=*(struct VirtualEntry **)(object+0xC); table[56].call(object+table[56].delta); } }
