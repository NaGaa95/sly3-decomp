// SLY3_CFLAGS: -Os -G0
#include "card_directory_records.h"
#include "eval_dispatch_api.h"

struct SaveSelectionSlot {
    unsigned char payload[0x6808];
    struct CardConvertedRecord metadata;
};
struct SaveSelectionView {
    unsigned char opaque00[0x24];
    struct SaveSelectionSlot slots[3];
    unsigned char opaque13950[4];
    struct SaveSelectionSlot *latest;
};
struct KEY;
extern struct KEY *D_004794EC;
CRef *func_002BC010(CRef *output, struct KEY *key, unsigned char *buffer);
int func_001CF3B8(void *first, void *second);

void func_001CF578(void *save)
{
    struct SaveSelectionView *context = save;
    int index;
    context->latest = &context->slots[0];
    for (index = 0; index < 3; ++index) {
        struct SaveSelectionSlot *slot = &context->slots[index];
        CRef value;
        float present;
        func_002BC010(&value, D_004794EC, slot->payload);
        present = value.payload.real;
        func_0012BC20(&value);
        if (present != 0.0f &&
            func_001CF3B8(&context->latest->metadata, &slot->metadata) < 0)
            context->latest = slot;
    }
}
