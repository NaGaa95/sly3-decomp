// Return the first available resource while walking the original parent chain.
// Reference algorithm: src/hand/func_001974C8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0x18]; struct S * parent; char unknown_1C[0x74]; void * resource; };
void *func_00226B78(struct S *object){while(object){if(object->resource)return object->resource;object=object->parent;}return 0;}
