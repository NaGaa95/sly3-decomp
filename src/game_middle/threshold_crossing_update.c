// SLY3_CFLAGS: -Os -G0
#include "threshold_crossing_api.h"
struct ThresholdEvent { float value; unsigned short side; unsigned short bit_index; };
static __inline__ unsigned int *BitsetWord(unsigned int *base, unsigned int word_index)
{
    return (unsigned int *)((unsigned int)base + word_index * sizeof(*base));
}

int func_001EDD80(void *event_storage, int i, float g, void *bit_storage, int f)
{
    struct ThresholdEvent *ae = (struct ThresholdEvent *)event_storage;
    unsigned int *grf = (unsigned int *)bit_storage;
    if (g <= ae[i].value) {
        struct ThresholdEvent *pe = &ae[i];
        for (;;) {
            if (pe->value < g) break;
            if (pe->side == f) {
                unsigned int bit = pe->bit_index;
                unsigned int w = bit / 32;
                unsigned int b = bit - w * 32;
                if (!f) *BitsetWord(grf, w) |= 1U << b;
                else *BitsetWord(grf, w) -= 1U << b;
            }
            i--;
            pe = &ae[i];
        }
    } else {
        struct ThresholdEvent *pe;
        i++;
        pe = &ae[i];
        for (;;) {
            if (g < pe->value) break;
            if (pe->side == f) {
                unsigned int bit = pe->bit_index;
                unsigned int w = bit / 32;
                unsigned int b = bit - w * 32;
                if (f) *BitsetWord(grf, w) |= 1U << b;
                else *BitsetWord(grf, w) -= 1U << b;
            }
            i++;
            pe = &ae[i];
        }
        i--;
    }
    return i;
}
