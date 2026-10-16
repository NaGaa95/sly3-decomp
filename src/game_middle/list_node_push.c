// SLY3_CFLAGS: -Os -G0
struct ListNode { void *first; void *second; struct ListNode *next; };
struct ListOwner { unsigned char opaque[0x30]; struct ListNode *head; };
extern char D_00475480[];
struct ListNode *func_0025D5A8(void *pool);
struct ListNode *func_001C7ED8(void *receiver)
{
    struct ListOwner *owner = (struct ListOwner *)receiver;
    struct ListNode *node = func_0025D5A8(D_00475480);
    node->next = owner->head;
    owner->head = node;
    return node;
}
