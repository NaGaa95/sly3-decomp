// SLY3_CFLAGS: -Os -G0
#include "deferred_callback_api.h"
struct DEFERRED_CALLBACK *func_0011E118(void *pool);
void func_0011AD80(void *list,struct DEFERRED_CALLBACK *node);
void func_0015DC68(void *game,void *receiver,struct DEFERRED_PMF member,void *owner) {
    struct DEFERRED_CALLBACK *node=func_0011E118((char *)game+0x442C);
    node->receiver=receiver;
    node->member=member;
    node->owner=owner;
    func_0011AD80((char *)game+0x4444,node);
}
