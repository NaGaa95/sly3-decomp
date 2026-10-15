// Reset the stored owner and clear both object state groups through their original methods.
// Reference algorithm: src/hand/func_0021BBD0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char prefix[0x10D0]; void *owner; };
void func_00170328(void *owner);
void func_002543F8(struct S *object);
void func_002544D8(struct S *object);
void func_002542E8(struct S *object)
{
    func_00170328(object->owner);
    func_002543F8(object);
    func_002544D8(object);
}
