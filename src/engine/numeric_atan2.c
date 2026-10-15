// SLY3_CFLAGS: -Os -G0
#include "eval_dispatch_api.h"
float func_002A3EE8(float y,float x);
CRef *func_00124450(CRef *result,int unused_count,CRef *arguments,EvalFrame *unused_frame) {
    float values[2];
    int i;
    for(i=0;i<2;++i) {
        CRef *value=&arguments[i];
        if(value->tag==20) values[i]=value->payload.real;
        else values[i]=value->payload.integer;
    }
    result->payload.real=func_002A3EE8(values[0],values[1]);
    result->tag=20;
    return result;
}
