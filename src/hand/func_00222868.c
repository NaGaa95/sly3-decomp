// Reset the receiver only when its active state is set.
// Reference algorithm: src/hand/func_00217FB8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x40]; int active; };
void func_00222CD8(struct S *p);
void func_00222868(struct S *p)
{
    if (p->active) func_00222CD8(p);
}
