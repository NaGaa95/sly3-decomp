// SLY3_CFLAGS: -Os -G0
struct Cycle { unsigned char prefix[0x14]; int count; int cursor; int items[1]; };
int func_0011E8F0(int low,int high);
void *func_00291F38(void *destination,void *source,int bytes);
static inline void Swap(int *a,int *b)
{
    int t=*a;
    *a=*b;
    *b=t;
}
void func_0022B398(void *owner,struct Cycle *cycle)
{
    int index;
    int previous;
    if(cycle->count>=2) {
        previous=cycle->items[0];
        if(cycle->cursor==cycle->count) {
            for(index=0;index<cycle->count;index++) {
                int other=func_0011E8F0(0,cycle->count-1);
                Swap(&cycle->items[index],&cycle->items[other]);
            }
            if(cycle->items[0]==previous) {
                int lastIndex=cycle->count-1;
                cycle->items[0]=cycle->items[lastIndex];
                cycle->items[lastIndex]=previous;
            }
            cycle->cursor=0;
        } else {
            func_00291F38(cycle->items,cycle->items+1,(cycle->count-1)*4);
            cycle->items[cycle->count-1]=previous;
            cycle->cursor++;
        }
    }
}
