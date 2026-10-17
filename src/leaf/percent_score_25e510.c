// SLY3_CFLAGS: -Os -G0
struct Group { int kind; void *table; };
extern struct Group D_00349B68[];
static inline int Min(int a,int b)
{
    return a<b?a:b;
}
void func_0025E348(struct Group *group,int *first,int *second,void *value);
int func_0025E510(void *value)
{
    int total=0;
    int count=0;
    int i;
    int percent;
    int result;
    int limit;
    for(i=0;i<9;i++) {
        int first=0;
        int second=0;
        func_0025E348(&D_00349B68[i],&first,&second,value);
        total+=first;
        count+=second;
    }
    if(!total)
        return 0;
    if(!count)
        return 0;
    if(count==total)
        return 100;
    limit=99;
    percent=count*100/total;
    result=1;
    if(percent>0)
        result=Min(limit,percent);
    return result;
}
