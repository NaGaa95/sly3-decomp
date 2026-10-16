// SLY3_CFLAGS: -Os -G0
#include "activation_selector_api.h"
struct RequestPermissionOwner {
    char opaque00[0x500];
    char context[0x19E0 - 0x500];
    int state;
    char opaque19E4[0x1F2C - 0x19E4];
    void *request;
    void *property;
    float last_time;
};
extern float D_0036BB98;
int func_001B5DD8(void *context, int ignored_event);
int func_00153668(void *receiver, int event);
void *func_001FE728(void *receiver, int flags);
int func_001C3DB8(void *receiver, int event)
{
    struct RequestPermissionOwner *owner = (struct RequestPermissionOwner *)receiver;
    if (owner->request && func_00239E70(owner->request) != 0x1A0 &&
        event != 0x2000 && event != 0x4000) {
        if (owner->property && 0.5f < D_0036BB98 - owner->last_time) {
            owner->last_time = D_0036BB98;
            func_001FE728(owner->property, 1);
        }
        return 1;
    }
    switch (owner->state) {
    case 4: case 9: case 17:
        if (event == 0x4000)
            return 1;
        break;
    case 8:
        if (func_001B5DD8(owner->context, event))
            return 1;
        break;
    }
    return func_00153668(receiver, event);
}
