// Evaluate the stored value against the original global curve, target and timestep without requesting a derivative.
// Reference algorithm: src/hand/func_001D00D0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
#include "approach_curve.h"
extern const struct ApproachCurve D_00325EA8;
extern float D_0036BB9C;
struct S { char unknown_0[0x224]; float value; };
float func_00216318(struct S *object){return func_0011E598(object->value,D_00325EA8.terminal,&D_00325EA8,0,D_0036BB9C);}
