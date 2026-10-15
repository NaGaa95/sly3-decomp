// Controller suppression counters and first/last transition notifications.
// The original reset-word view is reused without changing its shared header.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "input_controller.h"
struct INPUT_COUNT_GLOBAL;
extern "C" INPUT_COUNT_GLOBAL D_00370AC8;
extern "C" void func_001C4F70(INPUT_COUNT_GLOBAL *);
extern "C" void func_001C4FC0(INPUT_COUNT_GLOBAL *);
extern "C" void func_001A97B8(INPUT_CONTROLLER *);
extern "C" void func_001A9630(INPUT_CONTROLLER *input,unsigned int flags) {
    ++input->reset1180[0];
    if(flags&1) {
        if(++input->reset1180[2]==1)func_001C4F70(&D_00370AC8);
    }
    if(flags&2)++input->reset1180[3];
    if(flags&4)++input->reset1180[4];
    func_001A97B8(input);
}
extern "C" void func_001A96C8(INPUT_CONTROLLER *input,unsigned int flags) {
    --input->reset1180[0];
    if(flags&1) {
        if(--input->reset1180[2]==0)func_001C4FC0(&D_00370AC8);
    }
    if(flags&2)--input->reset1180[3];
    if(flags&4)--input->reset1180[4];
    func_001A97B8(input);
}
