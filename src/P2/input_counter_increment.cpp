// Standalone controller counter1184 increment.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "input_controller.h"
extern "C" void func_001A9770(INPUT_CONTROLLER *input) { ++input->reset1180[1]; }
