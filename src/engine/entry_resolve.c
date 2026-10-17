// SLY3_CFLAGS: -Os -G0
extern char D_00475480[];
struct ResolveEntry { short delta,padding; int (*fn)(void *); };
struct ResolveSlot { void *handle; int found; };
struct ResolveOwner { unsigned char prefix[0x18]; int count; struct ResolveSlot slots[8]; unsigned char gap[0xEC-0x5C]; struct ResolveEntry *table; };
void *func_0017E1B8(void *game,int flags,void *key,int context);
int func_0013B500(void *object,int kind);
void func_0015BE30(struct ResolveOwner *owner)
{
    int i;
    int context=owner->table[1].fn((char *)owner+owner->table[1].delta);
    for(i=0;i<owner->count;i++) {
        struct ResolveSlot *slot=&owner->slots[i];
        if(!slot->found) {
            void *object=func_0017E1B8(D_00475480,4,slot->handle,context);
            if(object && func_0013B500(object,0x2F)) {
                slot->handle=object;
                slot->found=1;
            }
        }
    }
}
