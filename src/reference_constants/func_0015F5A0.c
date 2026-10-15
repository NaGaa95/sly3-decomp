// Reference algorithm: src/hand/func_0014B1A0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_00251A58(void *,int);
void func_00251000(void *p);
void func_0015F5A0(char *p) { func_00251000(p); *(void **)(p + 0x17F8) = 0; func_00251A58(p, 0); }
