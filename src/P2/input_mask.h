#ifndef SLY3_PRIVATE_INPUT_MASK_H
#define SLY3_PRIVATE_INPUT_MASK_H
// Only the vptr, pending mask and timestamp fields are currently recovered.
// This layout does not assign an original dynamic class name.
struct INPUT_MASK_BASE { char prefix[0x2C];void *vtable; };
struct INPUT_MASK_BUFFERED { INPUT_MASK_BASE base;unsigned int pending30; };
struct INPUT_MASK_TIMED {
    INPUT_MASK_BASE base;
    char prefix30[0x1070-0x30];
    float timestamps1070[16];
};
struct INPUT_MASK_CLOCK { float now,step; };
extern "C" INPUT_MASK_CLOCK D_0036BB98;
extern "C" const float D_00322320;
#endif
