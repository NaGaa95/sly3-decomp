// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0
#include "state_emitter_shared.h"

struct RuntimeSixRequestOwner {
    unsigned char opaque00[0x0c];
    void *vtable;
    unsigned char opaque10[0x40];
    struct PositionRequest request[6];
    unsigned char opaque110[0x40];
};
typedef char RuntimeRequestArrayAt50[((unsigned int)&(((struct RuntimeSixRequestOwner *)0)->request)) == 0x50 ? 1 : -1];
typedef char RuntimeRequestOwnerSize150[sizeof(struct RuntimeSixRequestOwner) == 0x150 ? 1 : -1];
void *func_002B52F0(void *storage);
extern char D_0035ED00[];

void *func_002B5638(void *storage)
{
    struct RuntimeSixRequestOwner *owner = storage;
    struct PositionRequest *request;
    int remaining = 5;
    func_002B52F0(owner);
    owner->vtable = D_0035ED00;
    request = owner->request;
    do {
        func_002B8750(request);
        ++request;
    } while (--remaining != -1);
    return owner;
}
