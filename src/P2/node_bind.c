// SLY3_CFLAGS: -Os -G0
struct Node { void *object; unsigned char gap4[0x10]; void *first,*second; int inside; unsigned short flags; unsigned char gap22[0x7A]; int slot; };
struct Receiver {
    unsigned char prefix[0x470];
    unsigned char firstDefault[0x100],secondDefault[0x100];
    void *first,*second;
    unsigned char list[0x10];
    void *anchor;
};
int func_001C8F20(void *object,void *anchor);
void func_002896D0(struct Receiver *receiver,struct Node *node)
{
    node->slot=-1;
    node->inside=func_001C8F20(node->object,receiver->anchor);
    if(node->inside) {
        if(node->flags&0x100)
            node->first=receiver->first;
        if(node->flags&0x200)
            node->second=receiver->second;
    } else {
        if(node->flags&0x100)
            node->first=receiver->firstDefault;
        if(node->flags&0x200)
            node->second=receiver->secondDefault;
    }
}
