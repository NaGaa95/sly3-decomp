// Initialize the inherited object and global default resource, then set its scale to one.
// Reference algorithm: src/hand/func_00155560.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char prefix[0x5C]; float scale; };
void func_001C7340(struct S *object);
void func_00213988(void);
void func_0021A8F0(struct S *object)
{
    func_001C7340(object);
    func_00213988();
    object->scale = 1.0f;
}
