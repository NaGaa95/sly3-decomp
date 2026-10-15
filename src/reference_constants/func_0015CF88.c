// Reference algorithm: src/hand/func_00221388.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern char D_00479BBC[]; void func_0011B028(void *,void *);
void func_001C85C0(void *p); void func_0015CF88(char *p) { func_001C85C0(p); if(!(*(unsigned long *)(p + 0x28) & (1UL << 60))) func_0011B028(D_00479BBC, p); }
