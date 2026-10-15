// Store the explicit selection value and notify the original update method with selector 0.
// Reference algorithm: src/hand/func_001F0198.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x84]; int value; };
void func_00208B20(struct S *p, int selector);
void func_00209470(struct S *p, int value)
{
    p->value = value;
    func_00208B20(p, 0);
}
