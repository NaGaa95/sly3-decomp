// SLY3_CFLAGS: -Os -G0
#include "deferred_callback_api.h"
struct FlagSelf { unsigned char prefix[0x28]; unsigned long flags; };
extern unsigned char D_00475480[];
extern struct DEFERRED_PMF D_00320868;
void func_0015DD68(void *game, unsigned int mask, void *receiver, struct DEFERRED_PMF member, void *owner);
void func_0011AF60(void *list, void *item);

void func_0015CFD8(struct FlagSelf *self)
{
    if (self->flags & (1UL << 60)) {
        func_0015DD68(D_00475480, 3, self, D_00320868, 0);
        func_0011AF60(D_00475480 + 0x473C, self);
    }
}

