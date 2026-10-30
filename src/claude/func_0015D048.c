// SLY3_CFLAGS: -Os -G0
#include "deferred_callback_api.h"
struct FlagSelf { unsigned char prefix[0x28]; unsigned long flags; };
extern unsigned char D_00475480[];
extern struct DEFERRED_PMF D_00320868;
void func_0011B028(void *list, void *item);

void func_0015D048(struct FlagSelf *self)
{
    if (self->flags & (1UL << 60)) {
        func_0015DCD0(D_00475480, self, D_00320868, 0);
        func_0011B028(D_00475480 + 0x473C, self);
    }
}
