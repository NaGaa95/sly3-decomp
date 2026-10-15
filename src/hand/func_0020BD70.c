// Remove the object from its stored doubly linked list and finish its original cleanup.
// Reference algorithm: src/hand/func_001A2388.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { int unknown; void *list; };
void func_0011B028(void *list, struct S *object);
void func_0020BDC0(struct S *object);
void func_0020BD70(struct S *object)
{
    func_0011B028(object->list, object);
    func_0020BDC0(object);
}
