// Apply the inherited update and insert the explicit object in the original global doubly linked list.
// Reference algorithm: src/hand/func_0014B1A0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00479370[];
void func_001C85E8(void *object);
void func_0011AF60(void *list, void *object);
void func_00273CC0(void *object)
{
    func_001C85E8(object);
    func_0011AF60(D_00479370, object);
}
