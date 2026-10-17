// SLY3_CFLAGS: -Os -G0
struct Pending { void *item; int second; };
struct PendingOwner { unsigned char prefix[0x54]; int count; struct Pending entries[1]; };
struct PendingState { unsigned char prefix[0x278]; int index; int expected; unsigned char gap280[0x18]; int active; };
int func_002795C0(void *owner,struct Pending *entry);
int func_00279568(struct PendingOwner *owner)
{
    struct PendingState *state=(struct PendingState *)owner;
    if(!state->active)
        return 0;
    if(state->index<owner->count && state->expected!=owner->entries[state->index].second)
        return 0;
    return func_002795C0(owner,&owner->entries[state->index]);
}
