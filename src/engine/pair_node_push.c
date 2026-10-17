// SLY3_CFLAGS: -Os -G0
struct PushKey { unsigned char prefix[0x60]; int key; struct PushNode *head; };
struct PushNode { int pad0; struct PushNode *next; int pad8; int key; };
void *func_0011E118(void *pool);
struct PushNode *func_0013C5B8(char *world,struct PushKey *list,struct PushKey *item)
{
    struct PushNode *node=(struct PushNode *)func_0011E118(world+0x4494);
    node->key=item->key;
    node->next=list->head;
    list->head=node;
    return node;
}
