// SLY3_CFLAGS: -Os -G0
struct State { unsigned char prefix[0x70]; unsigned long flags; };
struct Target { unsigned char prefix[0xDC]; struct State *state; };
struct Request { unsigned char prefix[4]; struct Target *target; unsigned char gap8[0x10]; unsigned long flags; };
struct Group { unsigned char prefix[0x204]; struct Target *second; unsigned char gap208[0xDC]; struct Target *first; };
int func_0013B500(void *object,int kind);
int func_00287780(struct Group *group,struct Request *request)
{
    if(group) {
        if((void *)request->target==(void *)group)
            return 0;
        if(request->target==group->first)
            return 0;
        if(request->target==group->second)
            return 0;
    }
    if(request->flags&0x20000)
        return 0;
    if(func_0013B500(request->target,0x65))
        return 1;
    if((request->flags&0x10000) || (request->target->state->flags&4))
        return 0;
    return 1;
}
