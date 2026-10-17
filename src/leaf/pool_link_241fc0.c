// SLY3_CFLAGS: -Os -G0
struct ListHead { void *first; void *last; int nextOffset; };
struct Node { void *owner; struct ListHead children; };
struct Owner { unsigned char prefix[0x128]; unsigned long flags; };
extern unsigned char D_0047A434[];
void *func_0011E118(void *pool);
void func_0011AD60(void *list,int offset);
void func_0011AF60(void *list,void *node);
void func_00242048(void *owner,void *node);
void func_00241FC0(struct Owner *owner)
{
    if(!(owner->flags&0x40)) {
        struct Node *node;
        owner->flags|=0x40;
        node=func_0011E118(D_0047A434);
        node->owner=owner;
        func_0011AD60(&node->children,12);
        func_0011AF60(D_0047A434+0x18,node);
        func_00242048(owner,node);
    }
}
