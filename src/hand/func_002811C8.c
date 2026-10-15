// Prepend the explicit linked node to the receiver collection and notify its original update method.
// Reference algorithm: src/hand/func_00119C08.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct Node { int unknown[2]; struct Node *next; };
struct S { char prefix[0x110]; struct Node *head; };
void func_0023E228(struct S *object);
void func_002811C8(struct S *object, struct Node *node)
{
    node->next = object->head;
    object->head = node;
    func_0023E228(object);
}
