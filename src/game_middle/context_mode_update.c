// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "common.h"

struct ContextUpdateOwner {
    char prefix[0x1A0];
    qword vector1A0;
};

struct ContextModeZeroResource {
    char prefix[0x24];
    float gain24;
    char gap28[0x34 - 0x28];
    float parameter34;
};

struct ContextModeOneResource {
    char prefix[0xB4];
    float gainB4;
    char gapB8[0xBC - 0xB8];
    float parameterBC;
};

struct ContextUpdate {
    struct ContextUpdateOwner *owner;
    int state;
    char gap08[0x14 - 0x08];
    void *optional14;
    int mode;
    char child1C[0x34 - 0x1C];
    float parameter34;
    char gap38[0xA4 - 0x38];
    struct ContextModeZeroResource *resourceA4;
    struct ContextModeOneResource *resourceA8;
};

extern qword D_00317560;
int func_00138AC8(void *optional);
void func_001BDBB0(void *context, int phase);
void func_0024E878(void *owner, float gain);
void func_001BEA30(void *child);

void func_001BE220(void *receiver)
{
    struct ContextUpdate *context = receiver;
    int state;

    do {
        state = context->state;
        switch (state) {
        case 0:
            context->owner->vector1A0 = D_00317560;
            if (!context->optional14 || func_00138AC8(context->optional14))
                func_001BDBB0(context, 1);
            break;
        case 1:
            context->owner->vector1A0 = D_00317560;
            switch (context->mode) {
            case 0:
                func_0024E878(context->owner, context->resourceA4->gain24);
                context->parameter34 = context->resourceA4->parameter34;
                func_001BEA30(context->child1C);
                break;
            case 1:
                func_0024E878(context->owner, context->resourceA8->gainB4);
                context->parameter34 = context->resourceA8->parameterBC;
                func_001BEA30(context->child1C);
                break;
            }
            break;
        case 2:
            context->owner->vector1A0 = D_00317560;
            if (!context->optional14 || func_00138AC8(context->optional14))
                func_001BDBB0(context, -1);
            break;
        }
    } while (state != context->state);
}
