// Reset the inherited object, initialize its embedded record with the stored owner, and clear its flags.
// Reference algorithm: src/hand/func_0014B1A0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char prefix[0x20]; int flags; int unknown; void *owner; int reserved; char record[1]; };
void func_00169E40(struct S *object);
void func_001F3D10(void *owner, void *record);
void func_00274798(struct S *object)
{
    func_00169E40(object);
    func_001F3D10(object->owner, object->record);
    object->flags = 0;
}
