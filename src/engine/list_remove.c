// SLY3_CFLAGS: -Os -G0
void func_001D2898(void *destination,const void *source,unsigned int count);
struct ListRemove { unsigned char prefix[0xE8]; int count; int items[8]; };
void func_00166228(struct ListRemove *owner,int value)
{
    int i;
    for(i=0;i<owner->count;i++) {
        if(owner->items[i]==value) {
            func_001D2898(&owner->items[i],&owner->items[i+1],(owner->count-1-i)*4);
            owner->count--;
            return;
        }
    }
}
