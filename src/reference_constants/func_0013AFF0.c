// Original USA entry 0x13aff0; ordinary C reconstruction.
// Complete original entry, actual call inputs and return/data flow reviewed independently.
// SLY3_CFLAGS: -Os -G0
struct Event  {
    int first,second,type;
};
int func_0013B030(void *,int,int);
int func_0013AFF0(void *p,struct Event *event)  {
    int result=0;
    if(event->type==2)result=func_0013B030(p,event->first,event->second);
    return result;
}
