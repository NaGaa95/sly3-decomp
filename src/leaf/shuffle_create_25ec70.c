// SLY3_CFLAGS: -Os -G0
#include "runtime_shuffle_access.h"
struct AllocationRequest { int bytes, alignment; };
struct ShuffleBlock {
    unsigned char prefix[0x60];
    struct SHUFFLED_IDENTIFIERS *second;
    struct SHUFFLED_IDENTIFIERS *first;
};
struct ShuffleOwner {
    unsigned char prefix[0x4FB0];
    struct ShuffleBlock *block;
};
extern char D_0036B118[];
void *func_001D2538(struct AllocationRequest *request);
void *func_001D27F0(unsigned int bytes);
void func_0025EC70(struct ShuffleOwner *owner)
{
    static const int firstIdentifiers[7] = {0x273, 0x274, 0x275, 0x276, 0x277, 0x278, 0x279};
    static const int secondIdentifiers[10] = {0x269, 0x26A, 0x26B, 0x26C, 0x26D, 0x26E, 0x26F, 0x270, 0x271, 0x272};
    struct AllocationRequest request;
    struct ShuffleBlock *block;
    if (!owner->block) {
        request.bytes = 0x68;
        request.alignment = 0x10;
        block = func_001D2538(&request);
        owner->block = block;
        block->first = func_002BF8A0(func_001D27F0(20), 7, firstIdentifiers, D_0036B118);
        block = owner->block;
        block->second = func_002BF8A0(func_001D27F0(20), 10, secondIdentifiers, D_0036B118);
    }
}
