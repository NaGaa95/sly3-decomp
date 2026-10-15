// Reference algorithm: src/hand/func_00156D98.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
int func_001731B0(void *); void func_00173228(void *); void func_00173498(char *p) { if(--*(int *)(p + 0x64) == 0 && func_001731B0(p)) func_00173228(p); }
