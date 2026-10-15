// Reference algorithm: src/hand/func_00146EE0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_001C9118(void *,int);
void func_0028FD70(void *p);
void func_001FE238(char *p) { func_0028FD70(p); *(void **)(p + 0xE4) = p; *(void **)(p + 0xE0) = p; func_001C9118(p, 0); }
