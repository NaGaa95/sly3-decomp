// Reference algorithm: src/hand/func_00210F50.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern char D_00355D90[]; void func_00169C18(void *); void func_00169CB0(char *p,int flags) { *(void **)(p + 0x1C) = D_00355D90; if (flags & 1) func_00169C18(p); }
