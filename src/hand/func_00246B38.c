// Decrement the original sixteen-bit reference count and invoke the complete destructor when it reaches zero.
// Reference algorithm: src/hand/func_00176060.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0x58]; short count; };
void func_002BF528(struct S *p,int flags);
void func_00246B38(struct S *p){if(--p->count==0){if(p)func_002BF528(p,3);}}
