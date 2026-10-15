// Reference algorithm: src/hand/func_001C4700.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern char D_004793C8[];
void func_0021C0F0(void *p, void *source);
int func_001D0630(void *unused, void *source) { func_0021C0F0(D_004793C8, source); return 0; }
