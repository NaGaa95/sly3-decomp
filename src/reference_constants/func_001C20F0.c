// Reference algorithm: src/hand/func_001CF5D0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct Entry { int a,b,c,d; }; void func_001C20D0(void *,int,int,int); void func_001C2138(void *,void *); void func_001C20F0(char *p,int index,int a,int b) { func_001C20D0(p, index, a, b); func_001C2138(p, (struct Entry *)(p + 0x2C) + index); }
