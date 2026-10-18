// SLY3_CFLAGS: -Os -G0
struct IndexedList { unsigned char prefix[0x1C]; int count; unsigned char gap20[8]; unsigned short current; unsigned char gap2A[0xE]; unsigned char list[1]; };
int func_0011AEF8(void *list);
void func_00237168(struct IndexedList *object);
static inline int Clamp(int value,int low,int high)
{
    if(value<low)
        return low;
    if(value>high)
        return high;
    return value;
}
void func_00237220(struct IndexedList *object,int value)
{
    unsigned short index;
    if(func_0011AEF8(object->list))
        return;
    index=Clamp(value,0,object->count-1);
    if(object->current!=index) {
        object->current=index;
        func_00237168(object);
    }
}
