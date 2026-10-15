// Reference algorithm: src/hand/func_001492B0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_001878E0(void *, int);
void func_001FCAC8(void *p);
void func_001878A0(char *p) { func_001FCAC8(p); if (*(int *)(p + 0xB8) == 8) func_001878E0(p, 0); }
