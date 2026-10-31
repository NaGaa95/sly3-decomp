// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Apply a collected pickup: with the split flag, share a random amount between the holder's two counters (the lower one is topped up first,
// the remainder is halved, an odd unit goes to the first); otherwise add a random amount to the global counter.
struct Pickup {
    unsigned char prefix0[0x1A0];
    float range[2];
    float altRange[2];
    int split;
};
struct Holder {
    unsigned char prefix0[0x190];
    int first, second;
};
extern char D_0036C700[];
void func_001F48F8(struct Holder *self, struct Pickup *pickup);
int func_0013B500(void *record, int kind);
float func_0011E940(float low, float high);
void func_002157D0(struct Holder *self, int first, int second);
void func_00215808(struct Holder *self, int first, int second);
int func_001852E0(void *pool);
void func_00185328(void *pool, int value);
static inline int Min(int a, int b) { return a < b ? a : b; }
void func_00215248(struct Holder *self, struct Pickup *pickup)
{
    func_001F48F8(self, pickup);
    if (!func_0013B500(pickup, 0x6C))
        return;
    if (pickup->split) {
        int amount = (int)func_0011E940(pickup->range[0], pickup->range[1]);
        int first = self->first, second = self->second;
        int diff = first - second;
        int addFirst = 0, addSecond = 0;
        int odd;
        if (diff < 0)
            addFirst = Min(amount, -diff);
        else if (diff > 0)
            addSecond = Min(amount, diff);
        amount -= addSecond + addFirst;
        odd = amount & 1;
        amount /= 2;
        if (odd) {
            int next = addFirst + 1;
            addSecond += amount;
            addFirst = next + amount;
        } else {
            addFirst += amount;
            addSecond += amount;
        }
        func_002157D0(self, first + addFirst, second + addSecond);
        func_00215808(self, self->first + addFirst, self->second + addSecond);
    } else {
        int amount = (int)func_0011E940(pickup->altRange[0], pickup->altRange[1]);
        func_00185328(D_0036C700, func_001852E0(D_0036C700) + amount);
    }
}
