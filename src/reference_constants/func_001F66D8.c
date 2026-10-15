// Reference algorithm: src/hand/func_00151648.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VirtualEntry { short adjustment; short reserved; void (*call)(void *,void *,void *); }; void func_0023F400(void *,void *); void func_001F66D8(char *p,void *source) { struct VirtualEntry *table; func_0023F400(p, source); table = *(struct VirtualEntry **)(p + 0xC); table[56].call(p + table[56].adjustment, source, p + 0x160); }
