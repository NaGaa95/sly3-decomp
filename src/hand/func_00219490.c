// Mark both notification fields and the float value absent.
// Reference algorithm: src/hand/func_0022C818.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0x45C]; int first; int second; float value; };
void func_00219490(struct S *object)
{
    object->second=-1;object->value=-1.0f;object->first=-1;
}
