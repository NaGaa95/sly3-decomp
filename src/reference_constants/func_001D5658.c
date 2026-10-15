// Reference algorithm: src/hand/func_00129518.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern char D_004BC230[]; void func_00283F70(void *); void func_001D5658(char *p) { func_00283F70(D_004BC230); if(p) *(int *)(p + 0x1C) |= 2; }
