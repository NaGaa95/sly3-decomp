// Initialize the original record on its first use and then increment its counter.
// Reference algorithm: src/hand/func_002079A0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0xC]; int count; };
void func_00259CA8(struct S *p,int option);
void func_00259D10(struct S *p){if(!p->count)func_00259CA8(p,0);++p->count;}
