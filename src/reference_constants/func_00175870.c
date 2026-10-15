// Reference algorithm: src/hand/func_001A3650.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern int D_0036AEAC; void func_001D2818(void *object); void func_00175870(char *p,int flags) { D_0036AEAC = *(int *)(p + 0x64); if (flags & 1) func_001D2818(p); }
