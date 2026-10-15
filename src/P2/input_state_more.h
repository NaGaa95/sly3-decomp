#ifndef SLY3_PRIVATE_INPUT_STATE_MORE_H
#define SLY3_PRIVATE_INPUT_STATE_MORE_H
#include "input_mask.h"
// A separate expanded view for the newly recovered scalar fields. The four
// mask-method source and header remain unchanged during parent review.
struct INPUT_STATE_BASE_VIEW {
    float leftX,leftY,leftAmount;
    float rightX,rightY,rightAmount;
    unsigned int held18;
    float leftStateTimes1C[2],rightStateTimes24[2];
    void *vtable2C;
};
struct INPUT_STATE_TIMED_VIEW {
    INPUT_STATE_BASE_VIEW base;
    char prefix30[0x1068-0x30];
    unsigned int previousMask1068;
    char prefix106C[4];
    float timestamps1070[16];
};
struct INPUT_STATE_OWNER_VIEW {
    char prefix134[0x134];void *selected134;
    char prefix138[0x140C-0x138];
    INPUT_MASK_BUFFERED buffered140C;
    void *provided1440;
};
extern "C" const unsigned short D_00345128[];
#endif
