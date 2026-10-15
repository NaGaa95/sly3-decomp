// Complete original inputs, full body and emitted sections independently reviewed.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct GAIN_OWNER {
    char unused_00[0x1D4];
    float targetGain;
};
#include "gain_control_api.h"
extern float D_00326EC8;
void func_00248DF8(void *receiver) {
    struct GAIN_OWNER *owner = (struct GAIN_OWNER *)receiver;
    int layer, channel;
    func_00248A10(owner, 1.0f);
    for (layer = 0; layer < 8; ++layer) {
        if (layer != 1) {
            for (channel = 0; channel < 4; ++channel) {
                func_00248A78(owner, channel, 1.0f, layer);
            }
        }
    }
    owner->targetGain = D_00326EC8;
}
