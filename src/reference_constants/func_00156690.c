// Reference algorithm: src/hand/func_001492B0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VirtualEntry { short adjustment,reserved; void (*call)(void *,int); }; int func_001566D0(void *,void *); void func_00156690(char *p,void *context) { if(func_001566D0(p, context)) { struct VirtualEntry *table = *(struct VirtualEntry **)(p + 0xC); table[99].call(p + table[99].adjustment, 0); } }
