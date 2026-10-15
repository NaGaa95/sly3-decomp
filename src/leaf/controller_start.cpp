// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "runtime_shuffle_pair_access.h"

struct ControllerRecord72 { unsigned char bytes[72]; };
struct ControllerStart {
    int mode;
    int available;
    struct ControllerRecord72 record;
    void *provider;
    int selected_id;
    int off_id;
    int on_id;
    struct RuntimeShufflePairBag pairs;
};
struct Game;
extern struct Game D_00475480;
extern "C" void *func_0017E1B8(struct Game *, int kind, int id, void *owner);
extern "C" void func_0025AD70(struct Game *, const struct ControllerRecord72 *);
extern "C" void func_00288C58(struct ControllerStart *, int mode);

typedef char ControllerRecordSize72[(sizeof(struct ControllerRecord72) == 72) ? 1 : -1];
typedef char ControllerProviderAt50[((unsigned int)&(((struct ControllerStart *)0)->provider) == 0x50) ? 1 : -1];
typedef char ControllerPairsAt60[((unsigned int)&(((struct ControllerStart *)0)->pairs) == 0x60) ? 1 : -1];

extern "C" void func_00288DE8(struct ControllerStart *controller,
                   const struct ControllerRecord72 *record, int id, int mode)
{
    switch (controller->mode) {
    case 0:
        break;
    case 1:
        return;
    case 2:
        func_00288C58(controller, 0);
        break;
    case 3:
        return;
    }
    controller->provider = func_0017E1B8(&D_00475480, 0x405, id, 0);
    if (!controller->provider) {
        func_0025AD70(&D_00475480, record);
        return;
    }
    controller->available = 1;
    controller->record = *record;
    controller->selected_id = id;
    if (id == 0x36B) {
        struct RuntimeShufflePair pair = func_002C0060(&controller->pairs);
        controller->off_id = pair.first;
        controller->on_id = pair.second;
    } else {
        controller->off_id = 0x376;
        controller->on_id = 0x378;
    }
    func_00288C58(controller, mode);
}
