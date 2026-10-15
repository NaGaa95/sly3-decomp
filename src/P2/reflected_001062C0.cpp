// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
CRef *func_0024B2B8(CRef *,int,CRef *,int *,...);
}
struct EmbeddedDispatchEntry { short delta; short padding; void (*function)(void *); };
struct DispatchOwnerTableView { char prefix[0x21c]; EmbeddedDispatchEntry *table; };
extern "C" CRef *func_001062C0(CRef *output,void *receiver,int count,CRef *values)
{
    CRef temporary;
    func_0024B2B8(&temporary,0,values,0);
    func_0012BC20(&temporary);
    func_0012BDD8(&temporary,0x22);
    DispatchOwnerTableView *owner=(DispatchOwnerTableView *)receiver;
    EmbeddedDispatchEntry *entry=&owner->table[3];
    char *embedded=(char *)receiver+0x130;
    entry->function(embedded+entry->delta);
    func_0012AF00(output,&temporary);
    func_0012BC20(&temporary);
    return output;
}
