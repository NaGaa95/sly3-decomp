// SLY3_CFLAGS: -Os -G0
struct ContainsOwner { unsigned char prefix[0x380]; int count1; int list1[8]; int count2; int list2[8]; };
int func_00170C28(struct ContainsOwner *owner,int value)
{
    int i;
    for(i=0;i<owner->count1;i++) if(value==owner->list1[i]) return 1;
    for(i=0;i<owner->count2;i++) if(value==owner->list2[i]) return 1;
    return 0;
}
