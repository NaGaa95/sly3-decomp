// SLY3_CFLAGS: -Os -G0
struct Method { short adjustment, word2; void *function; };
struct NotifyTable { unsigned char prefix[0x2A0]; struct Method notify; };
struct MaskTable { unsigned char prefix[0x10]; struct Method mask; };
struct LinkNode {
    unsigned char prefix[0x1C];
    void *link;
};
struct LinkOwner {
    unsigned char prefix[0xC];
    struct NotifyTable *methods;
};
struct LinkHolder {
    unsigned char prefix[0x2C];
    struct MaskTable *maskTable;
    unsigned char gap30[0x1108 - 0x30];
    struct LinkNode *pendingNode;
    struct LinkOwner *pendingOwner;
    struct LinkNode *currentNode;
    struct LinkOwner *currentOwner;
    unsigned char gap1118[0x1180 - 0x1118];
    int busy;
};
extern char D_0036E6D0[];
void func_001A97B8(struct LinkHolder *holder)
{
    if (holder->currentNode) {
        holder->currentNode->link = 0;
    } else if (holder->currentOwner) {
        struct LinkOwner *owner = holder->currentOwner;
        ((void (*)(void *, void *))owner->methods->notify.function)((char *)owner + owner->methods->notify.adjustment, D_0036E6D0);
    }
    ((void (*)(void *, int))holder->maskTable->mask.function)((char *)holder + holder->maskTable->mask.adjustment, 0xFFFF);
    if (holder->pendingNode) {
        holder->pendingNode->link = holder;
    } else if (holder->pendingOwner && !holder->busy) {
        struct LinkOwner *owner = holder->pendingOwner;
        ((void (*)(void *, void *))owner->methods->notify.function)((char *)owner + owner->methods->notify.adjustment, holder);
    }
    holder->currentNode = holder->pendingNode;
    holder->currentOwner = holder->pendingOwner;
}
