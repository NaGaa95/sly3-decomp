// Return the original global resource predicate only when the stored selection is present.
// Reference algorithm: src/hand/func_0014C6A0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00475480[];
struct S { char unknown_0[0x6C]; int selection; char unknown_70[0x24]; void * resource; };
int func_00262128(void *global,void *resource);
int func_00261BD0(struct S *p){if(p->selection==-1)return 0;return !func_00262128(D_00475480,p->resource);}
