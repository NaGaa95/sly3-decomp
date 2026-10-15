// Reference algorithm: src/hand/func_00208208.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_0028FD70(void *); void func_0011AF38(void *,int); void func_001ECC10(char *p) { func_0028FD70(p); *(int *)(p+0x100)=-1; func_0011AF38(p+0x108,0x60); *(int *)(p+0x114)=-1; }
