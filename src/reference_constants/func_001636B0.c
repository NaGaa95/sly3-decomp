// Reference algorithm: src/hand/func_001B7000.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VirtualEntry { short delta,reserved; void (*call)(void *); }; void func_001633E0(void *,void *); void func_001636B0(char *p) { char *object=*(char **)(p+0x194); if(object) { struct VirtualEntry *table=*(struct VirtualEntry **)(object+0xC); table[54].call(object+table[54].delta); } func_001633E0(p,0); }
