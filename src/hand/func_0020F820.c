// Copy the current bounded value through its original getter/setter, clear the selections, and enable the object.
// Reference algorithm: src/hand/func_0016E380.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char prefix[0xC0]; int flags; char unknown[0x1C8 - 0xC4]; int selection; };
int func_001F43F0(struct S *object);
void func_001F43D0(struct S *object, int value);
void func_0020F868(struct S *object, int enabled);
void func_0020F820(struct S *object)
{
    func_001F43D0(object, func_001F43F0(object));
    object->selection = 0;
    object->flags = 0;
    func_0020F868(object, 1);
}
