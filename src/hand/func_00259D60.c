// Initialize the stored owner pointer, then reset the remaining selection fields.
// Reference algorithm: src/hand/func_001F0198.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { void *owner; };
void func_00259D80(struct S *p);
void func_00259D60(struct S *p, void *owner)
{
    p->owner = owner;
    func_00259D80(p);
}
