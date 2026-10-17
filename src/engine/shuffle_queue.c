// SLY3_CFLAGS: -Os -G0
extern char D_00474FF0[];
int func_00248858(void *context,int item);
void *func_002485D8(void *context,int item,int flag,void *child);
int func_0011E8F0(int low,int high);
void *func_00291F38(void *destination,void *source,int bytes);
void func_00147278(int unused,int count,int *items,int *cursor)
{
    int first,i;
    if(count<=0) return;
    first=items[0];
    if(func_00248858(D_00474FF0,first)) return;
    if(*cursor==count) {
        for(i=0;i<count;i++) {
            int j=func_0011E8F0(0,count-1);
            int t=items[i];
            items[i]=items[j];
            items[j]=t;
        }
        if(items[0]==first) {
            items[0]=items[count-1];
            items[count-1]=first;
        }
        *cursor=0;
    } else {
        func_00291F38(items,items+1,(count-1)*4);
        items[count-1]=first;
        (*cursor)++;
    }
    func_002485D8(D_00474FF0,items[0],0,0);
}
