// SLY3_CFLAGS: -Os -G0
struct Pair {
    int first;
    int second;
};
struct PairOwner {
    unsigned char prefix[0x130];
    struct Pair pair;
};
struct PairSelf {
    unsigned char prefix[0x130];
    struct Pair pair;
    int mode;
    struct PairOwner *owner;
};
extern int D_0047A424;
void func_00261250(void *self);
void func_0021E588(void *self);
void func_0021E028(void *self);
void func_0021E158(void *self);
void func_0021E3B8(void *self);
void func_0021E0C8(struct PairSelf *self)
{
    struct Pair next;
    func_00261250(self);
    if (self->mode != -1) {
        next.first = D_0047A424;
        next.second = self->owner->pair.first;
        if (next.first != self->pair.first || next.second != self->pair.second) {
            self->pair = next;
            func_0021E588(self);
        }
        func_0021E028(self);
        func_0021E158(self);
        func_0021E3B8(self);
    }
}
