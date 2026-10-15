// Initialize the inherited object, absent selections, and the original Sly 3 object kind.
// Reference algorithm: src/hand/func_00203568.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char prefix[0x138]; int first; int unknown; int second; int third; int kind; };
void func_001C7340(struct S *object);
void func_0021B4B8(struct S *object)
{
    func_001C7340(object);
    object->first = -1;
    object->kind = 0x7AF;
    object->second = -1;
    object->third = -1;
}
