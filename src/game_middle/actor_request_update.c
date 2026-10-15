// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Update the original CID52 actor's secondary request state.
#include "input_query_api.h"
struct RequestRecord {
    char prefix40[0x40];
    int phase;
};
struct RequestActor {
    char prefix134[0x134];
    void *input;
    char unused138[0x113C-0x138];
    void *optional_resource;
    char unused1140[0x19E8-0x1140];
    int secondary;
    char unused19EC[0x1F20-0x19EC];
    struct RequestRecord *record;
};
void func_001ADDD0(void *receiver, int state, int secondary);
void func_00279278(void *record);
int func_002503C8(void *receiver, float threshold);
void func_002791C8(void *record);
int func_00138AC8(void *resource);
void func_001B0070(struct RequestActor *p) {
    if (p->record->phase != 2) {
        func_001ADDD0(p, 0, -1);
        return;
    }
    switch (p->secondary) {
        case 8: {
            float threshold = 0.15f;
            if (func_001A7A80(p->input, 0xB0, threshold)) {
                func_00279278(p->record);
                return;
            }
            if (func_002503C8(p, threshold)) return;
            if (func_001A7A80(p->input, 0x40, threshold)) {
                func_001ADDD0(p, 0x18, 9);
                func_002791C8(p->record);
            }
            break;
        }
        case 9: {
            if (!p->optional_resource || func_00138AC8(p->optional_resource)) func_001ADDD0(p, 0x18, 8);
            break;
        }
    }
}
