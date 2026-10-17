// SLY3_CFLAGS: -Os -G0
struct Method { short delta,unused; void (*method)(void); };
struct Child { unsigned char prefix[0xC]; struct Method *methods; };
struct Owner { unsigned char prefix[0x10D0]; struct Child *child; };
static inline void CallChildInt(struct Child *child,int slot,void *value)
{
    ((void (*)(void *,void *))child->methods[slot].method)((char *)child+child->methods[slot].delta,value);
}
void func_0024D9A8(struct Owner *owner,struct Owner *other);
void func_00253A28(struct Owner *owner);
void func_00250B78(struct Owner *owner,struct Owner *other)
{
    struct Child *child=owner->child;
    func_0024D9A8(owner,other);
    owner->child=child;
    CallChildInt(child,45,other->child);
    func_00253A28(owner);
}
