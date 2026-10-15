// Reference algorithm: src/hand/func_0014FCC8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct Entry { int a,b,c; }; struct Entry *func_0017DBD0(char *p,int index) { return (struct Entry *)(p + 0x3020) + index; }
