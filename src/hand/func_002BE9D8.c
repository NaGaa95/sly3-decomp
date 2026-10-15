// Retain the explicit new object before releasing the stored old object and replacing its pointer; preserve the original retain/release order.
// Reference algorithm: src/hand/func_00144338.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S {void *resource;};
void func_0020BDB0(void *resource);
void func_0020BDC0(void *resource);
void func_002BE9D8(struct S *p,void *resource){if(resource)func_0020BDB0(resource);if(p->resource)func_0020BDC0(p->resource);p->resource=resource;}
