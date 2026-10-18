// SLY3_CFLAGS: -Os -G0
extern int D_00349BB0[];
static inline int Min(int a,int b)
{
    return a<b?a:b;
}
int func_0025E5E8(unsigned int kind,void *value);
int func_0025E6D0(void *value)
{
    int total;
    int count;
    int group;
    int percent;
    int result;
    int limit;
    total=0;
    count=0;
    for(group=0;group<9;group++) {
        int weight=D_00349BB0[group];
        count+=func_0025E5E8(group,value)*weight;
        total+=weight*100;
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
