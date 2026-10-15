// Update the inherited object and store whether its explicit entry is present in the owner collection.
// Reference algorithm: src/hand/func_00149358.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct R { char prefix[0x64]; void *list; };
struct S { char prefix[0xDC]; struct R *owner; char unknown[0x1BC - 0xE0]; int present; char unknown2[0x1D0 - 0x1C0]; void *entry; };
void func_0023E068(struct S *object);
int func_0026CBE8(void *list, void *entry);
void func_0026CC38(struct S *object)
{
    func_0023E068(object);
    if (object->entry) object->present = func_0026CBE8(object->owner->list, object->entry);
}
