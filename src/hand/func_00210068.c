// Allocate and construct the original callback with actual owner A1, integer tag, and receiver object A3, then store its returned pointer. Fixed-pool requested size is historically supplied but unused by the allocator; outer return type remains provisional because callers have not yet been classified.
// Reference algorithm: src/hand/func_00151648.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0x214]; void * callback; };
void *func_00169BF8(unsigned int requested_bytes);
void *func_00210658(void *receiver,void *owner,int tag,void *object);
void func_00210068(struct S *p,void *owner){p->callback=func_00210658(func_00169BF8(0x40),owner,11,p);}
