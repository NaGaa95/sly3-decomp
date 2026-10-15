// Reference algorithm: src/hand/func_001A5BF0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct CRef { short tag,reserved; int value; }; void func_0024B330(void *,void *,int,int,void *,void *); void func_0012BC20(void *); void func_001628C8(char *p,void *source) { struct CRef ref; func_0024B330(&ref, source, 0x2002, 0x20, p + 0x17F8, p + 0x17FC); func_0012BC20(&ref); }
