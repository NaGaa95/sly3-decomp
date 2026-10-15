// Compute the explicit scale ratio, update the stored scale, and apply that ratio through the original transform method.
// Reference algorithm: src/hand/func_00221268.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct R { char prefix[0xD0]; float scale; };
struct S { char prefix[0xD8]; struct R *record; };
void func_0023C4D0(struct S *object, float ratio);
void func_0023C4A0(struct S *object, float value)
{
    float ratio = value / object->record->scale;
    object->record->scale *= ratio;
    func_0023C4D0(object, ratio);
}
