// Return the stored owner predicate, or false when the owner is absent.
// Reference algorithm: src/hand/func_001A2358.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char prefix[0x1108]; void *owner; };
int func_00173428(void *owner);
int func_002BC5C0(struct S *object)
{
    int result=0;
    if(object->owner)result=func_00173428(object->owner)!=0;
    return result;
}
