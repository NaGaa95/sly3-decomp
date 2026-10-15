// Original null bindings fail each script gate.
// A0 is the controller; A1 is the actual unsigned binding-table index.
// The native CRef temporary supplies hidden outputA0, keyA1, environmentA2.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "input_table.h"
extern "C" int func_001A9318(const INPUT_TABLE_GATE_VIEW *input,unsigned int index) {
    const INPUT_TABLE_BINDING *binding=input->first1148[index];
    if(binding && func_002BC010(binding,D_00468D30).value.integer) return 1;
    return 0;
}
extern "C" int func_001A9370(const INPUT_TABLE_GATE_VIEW *input,unsigned int index) {
    const INPUT_TABLE_BINDING *binding=input->second1164[index];
    if(binding && func_002BC010(binding,D_00468D30).value.integer) return 1;
    return 0;
}
