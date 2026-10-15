// Reference algorithm: src/hand/func_00224068.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_0015CE68(void *);
void func_001C81B8(void *p); void func_0015CED0(char *p) { func_001C81B8(p); if (*(unsigned long *)(p + 0x28) & (1UL << 60)) func_0015CE68(p + 0x210); }
