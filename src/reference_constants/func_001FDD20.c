// Reference algorithm: src/hand/func_00130488.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void *func_001FDC18(void *, int);
int func_001FDD20(void *p, int mode) { void *result = func_001FDC18(p, mode); return *(int *)((char *)result + 0x20); }
