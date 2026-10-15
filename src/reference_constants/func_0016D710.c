// Reference algorithm: src/hand/func_001BBEA8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern char D_0036C700[]; void func_0016D840(void *,int); void func_001854C8(void *,int,void *); void func_00252FC0(void *,int);
void func_00238980(void *p);
void func_0016D710(char *p) { func_00238980(p); func_0016D840(p, -1); func_001854C8(D_0036C700, 0x19, *(void **)(p + 0x10)); func_00252FC0(*(void **)(p + 0x10), 0x29); }
