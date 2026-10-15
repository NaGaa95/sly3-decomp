// Store the explicit selection value and notify the original update method with selector 2.
// Reference algorithm: src/hand/func_001F0198.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x48]; int value; };
void func_00278E58(struct S *p, int selector);
void func_00279120(struct S *p, int value)
{
    p->value = value;
    func_00278E58(p, 2);
}
