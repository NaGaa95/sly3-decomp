// Initialize the inherited object and mark all three stored selections absent.
// Reference algorithm: src/hand/func_00182E80.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char prefix[0x138]; int first; int unknown; int second; int third; };
void func_001C7340(struct S *object);
void func_0021DEE8(struct S *object)
{
    func_001C7340(object);
    object->first = -1;
    object->second = -1;
    object->third = -1;
}
