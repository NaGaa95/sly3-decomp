// Store the explicit float value and update the original masked flag group.
// Reference algorithm: src/hand/func_0014D1D0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x54]; float value; };
void func_00245320(struct S *p, int mask, int flags);
void func_00244CA8(struct S *p, float value)
{
    p->value = value;
    func_00245320(p, 0x1FFF, 8);
}
