// Resolve the original global resource with all four explicit lookup inputs and store its returned pointer.
// Reference algorithm: src/hand/func_00120330.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00475480[];
struct S { char unknown_0[0x30]; void * resource; };
void *func_0017E1B8(void *global,int kind,int id,void *owner);
void func_00222800(struct S *p){p->resource=func_0017E1B8(D_00475480,1029,0x775,0);}
