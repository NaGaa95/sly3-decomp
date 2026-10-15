// SLY3_CFLAGS: -Os -G0
#include "eval_dispatch_api.h"
int func_0011E9F0(float first,float second,float epsilon);

CRef *func_001226C0(CRef *result,int unused_count,CRef *arguments,EvalFrame *unused_frame)
{
    float values[3];
    int i;
    int equal;
    for(i=0;i<3;i++) {
        CRef *value=&arguments[i];
        if(value->tag==0x13)
            values[i]=value->payload.integer;
        else
            values[i]=value->payload.real;
    }
    equal=func_0011E9F0(values[0],values[1],values[2])!=0;
    result->tag=0x15;
    result->payload.integer=equal;
    return result;
}
