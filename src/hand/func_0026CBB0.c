// Apply the explicit owner/object update and initialize the object rate to one tenth.
// Reference algorithm: src/hand/func_00182E80.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char prefix[0x98]; float rate; };
void func_0023E110(void *owner, struct S *object);
void func_0026CBB0(void *owner, struct S *object)
{
    func_0023E110(owner, object);
    object->rate = 0.1f;
}
