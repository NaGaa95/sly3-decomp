// SLY3_CFLAGS: -Os -G0
struct Method { short delta,unused; void (*method)(void); };
struct Subject { unsigned char prefix[0xC]; struct Method *methods; unsigned char gap10[0x120]; int stage; };
struct Other { unsigned char prefix[0x50]; unsigned int flags; };
static inline void CallSubjectInt(struct Subject *subject,int slot,int value)
{
    ((void (*)(void *,int))subject->methods[slot].method)((char *)subject+subject->methods[slot].delta,value);
}
int func_00277128(struct Subject *subject,struct Other *other)
{
    if(!(other->flags&2))
        return 0;
    if(subject->stage<3) {
        if(subject->stage>0)
            CallSubjectInt(subject,80,3);
    }
    return 1;
}
