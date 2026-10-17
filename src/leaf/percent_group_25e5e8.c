// SLY3_CFLAGS: -Os -G0
struct Group { int kind; void *table; };
extern struct Group D_00349B20[];
extern struct Group D_00349B68[];
static inline int Min(int a,int b)
{
    return a<b?a:b;
}
void func_0025E348(struct Group *group,int *first,int *second,void *value);
int func_0025E5E8(unsigned int kind,void *value)
{
    int first;
    int second;
    int third;
    int fourth;
    int total;
    int count;
    int percent;
    int result;
    int limit;
    if(kind>=9)
        return 0;
    first=0;
    second=0;
    func_0025E348(&D_00349B20[kind],&first,&second,value);
    third=0;
    fourth=0;
    func_0025E348(&D_00349B68[kind],&third,&fourth,value);
    total=first+third;
    count=second+fourth;
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
