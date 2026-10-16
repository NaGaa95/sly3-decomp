// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "notify_dispatch_api.h"
struct InstanceNotifyMethod {
    short delta, reserved;
    union {
        void (*simple)(void *);
        void (*restore)(void *, void *);
        void (*notify)(void *, int, int, int, void *const *, CRef *);
    } call;
};
struct InstanceNotifyObject {
    char prefix[0xC];
    InstanceNotifyMethod *table;
};
typedef char InstanceNotifyMethod8[sizeof(InstanceNotifyMethod) == 8 ? 1 : -1];

extern "C" int func_001FC768(InstanceNotifyObject *object, void *context)
{
    void *arguments[1];
    InstanceNotifyMethod *method = &object->table[32];
    method->call.simple(reinterpret_cast<char *>(object) + method->delta);
    arguments[0] = &context;
    method = &object->table[3];
    method->call.notify(reinterpret_cast<char *>(object) + method->delta,
                        18, 0, 1, arguments, 0);
    return 1;
}
