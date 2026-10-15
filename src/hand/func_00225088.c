// Initialize the inherited object and its embedded linked list with the original link offset, clearing the count.
// Reference algorithm: src/hand/func_0014B1A0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char prefix[0x48]; char list[0x60]; int count; };
void func_001C7340(struct S *object);
void func_0011AF38(void *list, int offset);
void func_00225088(struct S *object)
{
    func_001C7340(object);
    func_0011AF38(object->list, 0x10C);
    object->count = 0;
}
