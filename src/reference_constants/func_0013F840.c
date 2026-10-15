// Reference algorithm: src/hand/func_0012F8C0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
int func_001F1A08(void *,void *); int func_0013F840(char *p) { if(*(int *)(p + 0x11BC) == 3) return func_001F1A08(*(void **)(p + 0x11B4), p); return 0; }
