// SLY3_CFLAGS: -Os -G0
struct ChainRoot { unsigned char prefix[0x70]; unsigned long flags; };
struct ChainLink { unsigned char prefix[0x10]; struct ChainLink *next; };
struct ChainHead { unsigned char prefix[0x14]; int word14; unsigned char gap18[0xDC-0x18]; struct ChainRoot *root; };
struct ChainItem { unsigned char prefix[0x4]; struct ChainHead *head; unsigned char gap8[0x18-0x8]; unsigned long flags; };
struct ChainOwner { unsigned char prefix[0x14]; int word14; };
int func_0013B500(void *object,int kind);
void *func_00170528(void *owner,void *link);
int func_001709A8(struct ChainOwner *owner,struct ChainItem *item)
{
    struct ChainHead *head;
    struct ChainLink *link;
    if(item->flags&0x10000) return 0;
    head=item->head;
    if(head->root->flags&4) return 0;
    if(head->word14==owner->word14) return 0;
    for(link=(struct ChainLink *)head;link;link=link->next) {
        if(func_0013B500(link,0x32)) return 0;
        if(func_00170528(owner,link)) return 0;
    }
    return 1;
}
