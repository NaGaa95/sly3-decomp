// Resolve the stored owner through the original global lookup and return its record value or the absent sentinel.
// Reference algorithm: src/hand/func_001E79F0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct R { int value; };
extern char D_00474FF0[];
struct S { char unknown_0[0x60]; void * owner; };
struct R *func_00246E98(void *global,void *owner);
int func_00245A88(struct S *p){struct R *record=func_00246E98(D_00474FF0,p->owner);return record?record->value:-1;}
