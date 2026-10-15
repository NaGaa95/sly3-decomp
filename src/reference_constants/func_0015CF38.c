// Reference algorithm: src/hand/func_00221388.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern char D_00479BBC[]; void func_0011AF60(void *,void *);
void func_001C85E8(void *p); void func_0015CF38(char *p) { func_001C85E8(p); if(!(*(unsigned long *)(p + 0x28) & (1UL << 60))) func_0011AF60(D_00479BBC, p); }
