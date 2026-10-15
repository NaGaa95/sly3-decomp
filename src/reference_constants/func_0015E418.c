// Reference algorithm: src/hand/func_0017DDE8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern char D_00474FF0[]; void func_0015F050(void *,int); void func_00252FC0(void *,int); void func_00248ED0(void *); void func_00251A58(void *,int);
void func_00238980(void *p); void func_0015E418(char *p) { func_00238980(p); func_0015F050(p, -1); func_00252FC0(*(void **)(p + 0x10), 0x36); func_00248ED0(D_00474FF0); func_00251A58(*(void **)(p + 0x10), 1); }
