// Resolve the original global resource with all four explicit lookup inputs and store its returned pointer.
// Reference algorithm: src/hand/func_00170B60.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00475480[];
struct S { char unknown_0[0x30]; int id; void * resource; };
void *func_0017E1B8(void *global,int kind,int id,void *owner);
void func_0021EB48(struct S *p){p->resource=func_0017E1B8(D_00475480,5,p->id,0);}
