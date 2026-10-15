// SLY3_CFLAGS: -Os -G0
#include "eval_dispatch_api.h"
struct FrameBinding {
    char prefix[8];
    int key;
    CRef value;
    struct FrameBinding *next;
};
struct EvalFrame {
    char prefix[8];
    EvalFrame *parent;
    struct FrameBinding *bindings;
    int busy;
};
CRef *func_00129B58(EvalFrame *frame,int key,int searchParents) {
    CRef *result=0;
    struct FrameBinding *binding;
    frame->busy=1;
    for(binding=frame->bindings;binding;binding=binding->next) {
        if(binding->key==key) {
            result=&binding->value;
            goto done;
        }
    }
    if(!searchParents) goto done;
    if(frame->parent && !frame->parent->busy)
        result=func_00129B58(frame->parent,key,searchParents);
done:
    frame->busy=0;
    return result;
}
