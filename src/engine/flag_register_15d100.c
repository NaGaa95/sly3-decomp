// SLY3_CFLAGS: -Os -G0

#include "deferred_callback_api.h"
#define ACTIVE(self) ((int)((self)->flags >> 56) & 1)
#define QUEUED(self) ((int)((self)->flags >> 60) & 1)
struct FlagSelf { unsigned char prefix[0x28]; unsigned long flags; unsigned char gap30[0x3C - 0x30]; unsigned int tag; unsigned char gap40[0x210 - 0x40]; unsigned char node[1]; };
extern unsigned char D_00475480[];
extern unsigned char D_00479BBC[];
extern struct DEFERRED_PMF D_00320868;
int func_0015D0E0(struct FlagSelf *self);
void func_001C9118(struct FlagSelf *self, int mode);
void func_0015B640(void *game, void *node);
int func_0011B0C0(void *list, void *item);
void func_0011B028(void *list, void *item);
void func_0015B6B0(void *game, void *node);
int func_001C8610(void *self);
void func_0015DD68(void *game, unsigned int mask, void *receiver, struct DEFERRED_PMF member, void *owner);
void func_0011AF60(void *list, void *item);
static inline int ModeOf(struct FlagSelf *self, int enable)
{
    unsigned int tag;
    if(enable) {
        tag = self->tag;
        if((tag ^ 1) & 1) tag = *(unsigned int *)tag;
        if(!(tag & 2)) return 2;
    }
    return 0;
}
void func_0015D100(struct FlagSelf *self)
{
    int enable = func_0015D0E0(self);
    func_001C9118(self, ModeOf(self, enable));
    if(enable == QUEUED(self)) return;
    if(ACTIVE(self)) {
        if(self->flags & (1UL << 60)) func_0015B640(D_00475480, self->node);
        else if(func_0011B0C0(D_00479BBC, self)) func_0011B028(D_00479BBC, self);
    }
    {
        unsigned long f = self->flags;
        f &= ~(1UL << 60);
        f |= (unsigned long)(enable & 1) << 60;
        self->flags = f;
    }
    if(ACTIVE(self)) {
        if(self->flags & (1UL << 60)) func_0015B6B0(D_00475480, self->node);
        else if(func_001C8610(self)) {
            func_0015DD68(D_00475480, 3, self, D_00320868, 0);
            func_0011AF60(D_00475480 + 0x473C, self);
        }
    }
}
