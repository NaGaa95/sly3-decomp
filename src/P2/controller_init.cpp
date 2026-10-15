// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "runtime_shuffle_pair_access.h"
#include "heap.h"

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
extern "C" void func_00288C58(struct ControllerStart *, int mode);

typedef char ControllerRecordSize72[(sizeof(struct ControllerRecord72) == 72) ? 1 : -1];
typedef char ControllerProviderAt50[((unsigned int)&(((struct ControllerStart *)0)->provider) == 0x50) ? 1 : -1];
typedef char ControllerPairsAt60[((unsigned int)&(((struct ControllerStart *)0)->pairs) == 0x60) ? 1 : -1];

extern "C" struct RuntimeShufflePairBag *func_002BFE30(struct RuntimeShufflePairBag *);
extern "C" CLinearHeap D_004C4080;

extern "C" struct ControllerStart *func_00288BA8(struct ControllerStart *controller)
{
    func_002BFE30(&controller->pairs);
    controller->mode = -1;
    controller->selected_id = -1;
    controller->off_id = -1;
    controller->on_id = -1;
    controller->provider = 0;
    struct RuntimeShufflePair initial_pairs[3] = {
        {0x370,0x371}, {0x372,0x373}, {0x374,0x375}
    };
    func_002BFED8(&controller->pairs,3,initial_pairs,&D_004C4080);
    func_00288C58(controller,0);
    return controller;
}
