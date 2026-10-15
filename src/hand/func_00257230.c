// Decrement the active count and disable the object when it reaches zero.
// Reference algorithm: src/hand/func_00221268.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x115C]; int count; };
void func_001C9118(struct S *p, int enabled);
void func_00257230(struct S *p)
{
    if (--p->count == 0) func_001C9118(p, 0);
}
