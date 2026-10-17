// SLY3_CFLAGS: -Os -G0
struct Entry { short delta,unused; void (*method)(void *,int,void *); };
struct Target { unsigned char prefix[0xC]; struct Entry *vtable; };
struct Link { unsigned char prefix[4]; struct Target *target; unsigned char gap8[4]; struct Link *next; };
struct Message { void *sender; struct Target *target; };
struct Owner { unsigned char prefix[0x130]; struct Link *links; };
extern char D_00475480[];
void func_0023BBE0(struct Owner *owner);
void func_002811F0(struct Target *target,struct Link *link);
void func_00281178(void *game,struct Link *links);
void func_00280DF8(struct Owner *owner)
{
    struct Link *link;
    func_0023BBE0(owner);
    for(link=owner->links;link;link=link->next) {
        struct Message message;
        struct Entry *entry;
        message.sender=owner;
        message.target=link->target;
        func_002811F0(link->target,link);
        entry=&message.target->vtable[4];
        entry->method((char *)message.target+entry->delta,7,&message);
    }
    func_00281178(D_00475480,owner->links);
    owner->links=0;
}
