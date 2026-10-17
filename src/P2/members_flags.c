// SLY3_CFLAGS: -Os -G0
struct Method { short delta,unused; unsigned int (*method)(void); };
struct Member { unsigned char prefix[0xC]; struct Method *methods; };
struct Group { int unknown_0; int count; struct Member *members[1]; };
static inline unsigned int CallMember(struct Member *member,int slot)
{
    return ((unsigned int (*)(void *))member->methods[slot].method)((char *)member+member->methods[slot].delta);
}
unsigned int func_00238888(struct Group *group)
{
    int i;
    for(i=group->count-1;i>=0;i--) {
        unsigned int flags=CallMember(group->members[i],12);
        if(!(flags&0x1000))
            return flags;
    }
    return 0x1000;
}
