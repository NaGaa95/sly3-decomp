// Update the inherited object, attach its stored record to the owner, and activate the record.
// Reference algorithm: src/hand/func_00132100.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct R { char prefix[0x68]; int active; };
struct O { char prefix[0xA8]; struct R *record; };
struct S { char prefix[8]; struct O *owner; char unknown[0x1C-0xC]; struct R *record; };
void func_0012F288(struct S *object);
void func_0026EED0(struct S *object)
{
    func_0012F288(object);
    object->owner->record=object->record;
    object->record->active=1;
}
