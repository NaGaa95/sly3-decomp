// Reference algorithm: src/hand/func_001D7780.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern char D_00475480[]; void *func_0017E1B8(void *,int,int,void *); void func_00261050(void *,int); void func_001C4F18(void **p) { void *object=func_0017E1B8(D_00475480,0x405,0x424,0); *p=object; if(object)func_00261050(object,1); }
