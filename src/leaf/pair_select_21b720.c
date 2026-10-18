// SLY3_CFLAGS: -Os -G0
struct Pair {
    int first;
    int second;
};
struct PairOwner {
    unsigned char prefix[0x130];
    int slot;
    unsigned char gap134[0x1B8 - 0x134];
    int kind;
    unsigned char gap1BC[0x1D0 - 0x1BC];
    struct PairOwner *source;
};
struct PairSelf {
    unsigned char prefix[0x130];
    struct Pair pair;
    int mode;
    struct PairOwner *owner;
};
extern int D_0047A424;
void func_00261250(void *self);
void func_0021BC58(void *self);
void func_0021B6C0(void *self);
void func_0021B7E8(void *self);
void func_0021BA40(void *self);
void func_0021B720(struct PairSelf *self)
{
    struct Pair next;
    func_00261250(self);
    if (self->mode != -1) {
        next.first = D_0047A424;
        switch (self->owner->kind) {
        case 0:
            next.second = self->owner->slot;
            break;
        case 1: {
            struct PairOwner *source = self->owner->source;
            next.second = source ? source->slot : -1;
            break;
        }
        }
        if (next.first != self->pair.first || next.second != self->pair.second) {
            self->pair = next;
            func_0021BC58(self);
        }
        func_0021B6C0(self);
        func_0021B7E8(self);
        func_0021BA40(self);
    }
}
