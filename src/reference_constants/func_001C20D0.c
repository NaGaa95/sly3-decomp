// Reference algorithm: src/hand/func_00120820.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct Entry { int a,b,c,d; }; void func_001C20D0(char *p,int index,int a,int b) { struct Entry *entry = (struct Entry *)(p + 0x2C) + index; entry->a = a; entry->c = b; entry->b = 0; entry->d = 0; }
