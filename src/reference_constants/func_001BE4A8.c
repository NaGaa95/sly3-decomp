// SLY3_CFLAGS: -Os -G0
struct VirtualEntry { short delta,reserved; void (*call)(void *,int,int); }; void func_0023EBF8(void *,int); void func_001BE4A8(char *p) { char *object=*(char **)(p+0x40); if(object) { struct VirtualEntry *table=*(struct VirtualEntry **)(object+0xC); table[95].call(object+table[95].delta,0x3F,1); func_0023EBF8(object,0); } }
