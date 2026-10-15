// Mark both stored selections absent and apply the original default selection.
// Reference algorithm: src/hand/func_0020CE40.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char prefix[0x18]; int first; int unknown; int second; };
void func_0021E980(struct S *object, int selection);
void func_0021E6B8(struct S *object)
{
    object->first = -1;
    object->second = -1;
    func_0021E980(object, 0);
}
