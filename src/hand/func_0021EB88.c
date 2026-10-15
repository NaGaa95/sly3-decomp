// Clear the active state before initializing the remaining transition fields.
// Reference algorithm: src/hand/func_001F0198.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x34]; int active; };
void func_0021EBA8(struct S *p);
void func_0021EB88(struct S *p)
{
    p->active = 0;
    func_0021EBA8(p);
}
