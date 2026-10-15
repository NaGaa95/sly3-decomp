// Reference algorithm: src/hand/func_001D4EC8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_001A6850(void *,int); void func_00252FC0(void *,int); void func_001A6B00(void *,int);
void func_00238980(void *p);
void func_001A6520(char *p) { func_00238980(p); func_001A6850(p, -1); func_00252FC0(*(void **)(p + 0x10), 0x33); func_001A6B00(p, 0); }
