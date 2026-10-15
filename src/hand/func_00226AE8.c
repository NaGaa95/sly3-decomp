// Resolve the explicit resource key and store the returned object, using the stored fallback when absent.
// Reference algorithm: src/hand/func_0014B1A0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char prefix[0x14]; void *fallback; int unknown; void *selected; };
void *func_00226770(struct S *object, int key);
void func_00226AE8(struct S *object, int key)
{
    object->selected = func_00226770(object, key);
    if (!object->selected) object->selected = object->fallback;
}
