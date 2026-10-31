// SLY3_CFLAGS: -Os -G0
#include "deferred_callback_api.h"
struct SequencePairSelf { unsigned char prefix[0x14C]; void *other; int mode; };
extern char D_00475480[];
extern const struct DEFERRED_PMF D_00324B20;

void func_001E5070(struct SequencePairSelf *self, void *other, int mode)
{
    self->mode = mode;
    self->other = other;
    func_0015DCD0(D_00475480, self, D_00324B20, 0);
}
