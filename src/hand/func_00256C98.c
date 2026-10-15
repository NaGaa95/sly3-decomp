// Store both explicit float values and activate the receiver.
// Reference algorithm: src/hand/func_001F5860.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0x9C]; int active; float first; float second; };
void func_00256C98(struct S *object,float first,float second)
{
    object->active=1;object->first=first;object->second=second;
}
