// SLY3_CFLAGS: -Os -G0
#include "eval_dispatch_api.h"

CRef *func_001229A8(CRef *result,int unused_count,CRef *arguments,EvalFrame *unused_frame)
{
    CRef reference;
    func_0012BDD8(&reference,0);
    if(arguments[0].tag==0x1D) {
        ScriptNode *node=(ScriptNode *)arguments[0].payload.pointer;
        int i;
        for(i=0;node;node=node->next,i++) {
            if(i==arguments[1].payload.integer) {
                func_0012B3B0(&reference,&node->ref);
                break;
            }
        }
    }
    func_0012AF00(result,&reference);
    func_0012BC20(&reference);
    return result;
}
