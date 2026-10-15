// Return whether the object is absent from its stored owner list using the original membership predicate.
// Reference algorithm: src/hand/func_00119C08.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct T { char prefix[0x48]; char list[1]; };
struct S { char prefix[0x14]; struct T *owner; };
int func_0011B0C0(void *list, struct S *object);
int func_0022BB50(struct S *object)
{
    return !func_0011B0C0(object->owner->list, object);
}
