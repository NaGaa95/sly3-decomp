// Reference algorithm: src/hand/func_0017A558.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct Key { short first,second; union { short s; int i; } value; }; extern struct Key D_003255A0; extern char D_00475480[]; void func_001C85C0(void *); void func_0015DD68(void *,int,void *,struct Key,void *); void func_001FB580(char *p) { func_001C85C0(p); if(*(int *)(p+0xD4)==1)func_0015DD68(D_00475480,3,p,D_003255A0,0); }
