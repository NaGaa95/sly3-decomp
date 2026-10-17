// SLY3_CFLAGS: -Os -G0
#include "eval_dispatch_api.h"
struct PropertyMethod {
    short delta;
    short unused;
    void (*call)(void *, int, int, int, int, CRef *);
};
struct PropertyObject {
    unsigned char prefix[0xC];
    struct PropertyMethod *methods;
};
int func_001F4830(struct PropertyObject *object)
{
    CRef value;
    int result = 1;
    value.tag = 0x15;
    value.payload.integer = 1;
    object->methods[3].call((char *)object + object->methods[3].delta, 0x10, 0, 0, 0, &value);
    if (value.tag == 0x15)
        result = value.payload.integer;
    func_0012BC20(&value);
    return result;
}
