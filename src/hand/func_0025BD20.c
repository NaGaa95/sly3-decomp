// Drain the original stored resource chain until its helper clears the receiver pointer.
// Reference algorithm: src/hand/func_00156D98.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0x4784]; void * resource; };
void func_001739A8(void *resource);
void func_0025BD20(struct S *p){void *resource=p->resource;if(resource){do{func_001739A8(resource);resource=p->resource;}while(resource);}}
