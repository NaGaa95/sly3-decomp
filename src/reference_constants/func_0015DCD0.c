// SLY3_CFLAGS: -Os -G0
#include "deferred_callback_api.h"
void func_0015DCD0(void *game,void *receiver,struct DEFERRED_PMF member,void *owner) {
    struct DEFERRED_CALLBACK *node;
    for(node=*(struct DEFERRED_CALLBACK **)((char *)game+0x4444);node;node=node->next) {
        if(node->receiver==receiver && node->member.index==member.index && ((node->member.index!=-1 && node->member.target.vptrOffset==member.target.vptrOffset) || node->member.target.word==member.target.word) && node->owner==owner)return;
    }
    func_0015DC68(game,receiver,member,owner);
}
