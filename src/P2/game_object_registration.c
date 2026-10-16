// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "runtime_geometry_access.h"
struct RegistrationGame {
    char prefix[0x4F6C];
    unsigned int count;
    void *objects[4];
};
struct RegistrationGeometryView { char prefix[8]; void *data; };
void *func_001D2538(struct ALLOCREQ *request);

void func_001F4950(void *receiver, void *object)
{
    struct RegistrationGame *game = receiver;
    if (game->count < 4) {
        struct RegistrationGeometryView *record;
        game->objects[game->count++] = object;
        record = (struct RegistrationGeometryView *)func_002BCAD8((RuntimeOwner *)object, 1);
        if (!record->data) {
            struct ALLOCREQ request;
            request.cb = 0x10;
            request.cbAlign = 0x10;
            record->data = func_001D2538(&request);
        }
    }
}
