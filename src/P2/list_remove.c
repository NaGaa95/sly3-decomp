// SLY3_CFLAGS: -Os -G0
struct List { unsigned char prefix[0x64]; int count; int items[1]; };
void *func_00291F38(void *dest,const void *src,unsigned size);
void func_002261F0(struct List *list,int value)
{
    int i;
    for(i=0;i<list->count;i++) {
        int *item=&list->items[i];
        if(*item==value) {
            func_00291F38(item,item+1,(list->count-i)*4-4);
            list->count--;
            return;
        }
    }
}
