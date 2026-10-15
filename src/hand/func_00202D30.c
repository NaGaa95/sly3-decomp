// Release the old referenced object before retaining the new explicit object and storing its pointer. Both original reference helpers consume only pointer A0.
// Reference algorithm: src/hand/func_00132B78.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0x18]; void * resource; };
void func_0020BDC0(void *resource);
void func_0020BDB0(void *resource);
void func_00202D30(struct S *p,void *resource){if(p->resource)func_0020BDC0(p->resource);if(resource)func_0020BDB0(resource);p->resource=resource;}
