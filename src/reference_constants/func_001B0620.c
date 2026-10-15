// Reference algorithm: src/hand/func_00184208.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
int func_00156B98(void *,void *); int func_001B0620(char *p,void *context) { if(*(int *)(p + 0x1F1C)) return 1; return func_00156B98(p, context); }
