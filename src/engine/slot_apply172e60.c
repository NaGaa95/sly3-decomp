// SLY3_CFLAGS: -Os -G0
struct SlotApplyRecord { char prefix[0xE0]; int identifier; };
struct SlotApplyOwner {
    char prefix[0x4C]; void *source;
    struct SlotApplyRecord *current, *pending;
};
struct SlotApplyEntry { char prefix[0xC]; int identifier; };
extern char D_0036C700[];
int func_00172F48(void *owner);
int func_00173068(void *owner);
void func_00172D68(void *unused, struct SlotApplyRecord *record, int flag);
struct SlotApplyEntry *func_00185720(char *table, void *request);
int func_00173428(void *owner);
void func_00173228(void *owner);

void func_00172E60(struct SlotApplyOwner *owner, struct SlotApplyRecord *next)
{
    int identifier;
    int first,second,third;
    if(next==owner->current)
        return;
    identifier=-1;
    first=func_00172F48(owner);
    second=func_00173068(owner);
    func_00172D68(owner,owner->current,1);
    owner->current=next;
    owner->pending=0;
    func_00172D68(owner,next,0);
    if(owner->current && owner->current->identifier!=0x75C)
        identifier=owner->current->identifier;
    func_00185720(D_0036C700,owner->source)->identifier=identifier;
    third=func_00173428(owner);
    if((first && !third) || (second && third))
        func_00173228(owner);
}
