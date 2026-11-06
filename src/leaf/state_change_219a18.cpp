// Switch the target tracker to a new state: run the exit work of the old state (0: vtable hook, 1: release the owner), stamp the change times, run the entry work of the new state (counters, text ids, registry updates) and refresh the panel and the update flag for the states 2..7.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
}
class OptionReference {
public:
    CRef value;
    OptionReference(int integer) { value.tag = 0x13; value.payload.integer = integer; }
    OptionReference(const OptionReference &) __asm__("func_0012AF00");
    void Drop() __asm__("func_0012BC20");
    ~OptionReference() { Drop(); }
};
struct KEY;
struct Method { short delta, reserved; void (*call)(void *); };
struct Object {
    unsigned char pad00[0xC];
    Method *methods;
    unsigned char pad10[0x120 - 0x10];
    int field120;
    int field124;
};
struct Item { unsigned char pad[0x518]; int kind; };
struct Pair { Item *item; int count; };
struct Game {
    unsigned char pad[0x42C0];
    KEY *keys[2];
};
struct Self {
    unsigned char pad00[0xC];
    Method *methods;
    unsigned char pad10[0x3C - 0x10];
    int flags;
    Object *target;
    unsigned char pad44[0x58 - 0x44];
    int count;
    int state;
    float time;
    float time2;
    int active;
    Pair pairs[4];
    unsigned char pad8C[0x98 - 0x8C];
    int index;
    int counter;
    Object *owner;
    Object *panel;
    int flagA8;
    int flagAC;
};
struct Clock { float now; unsigned char pad[0x3C]; float t40; };
extern "C" {
extern Clock D_0036BB98;
extern unsigned char D_0036C700[];
extern unsigned char D_00375290[];
extern Game D_00475480;
extern unsigned char D_00468D30[];
extern int D_00349370[];
void func_001854C8(void *registry, int id, void *arg);
int func_0021A720(Self *self);
void func_00262540(Object *panel, int text, int value);
void func_00262450(Object *panel, int text);
int func_00260758(Object *panel, int id);
int func_001852E0(void *registry);
void func_00185328(void *registry, int value);
void func_002159D8(void *object, int mode);
void func_001CFE08(void *object);
void func_001A93C8(void *game, int a, int b);
void func_001A94A8(void *game, int a);
void func_001A94F0(void *game, int a);
void func_001A9420(void *game, int a, int b);
}
OptionReference QueryOption(KEY *, unsigned char *) __asm__("func_002BC010");
OptionReference WriteOption(KEY *, const OptionReference &, unsigned char *) __asm__("func_002BC050");
static inline void WriteRef(KEY *key, OptionReference ref, unsigned char *p)
{
    WriteOption(key, ref, p);
}
static inline void WriteInt(KEY *key, int value, unsigned char *p)
{
    OptionReference ref(value);
    WriteRef(key, ref, p);
}
static inline int ReadInt(KEY *key, unsigned char *p)
{
    return QueryOption(key, p).value.payload.integer;
}
#define CALL(o, m) ((o)->methods[m].call)((char *)(o) + (o)->methods[m].delta)
extern "C" void func_00219A18(Self *self, int newState)
{
    static const int kLabels[4] = { -1, 0x7A0, 0x7A1, 0x7A2 };
    static const int kTitles[4] = { 0x7A8, 0x7A9, 0x7AA, 0x7AB };
    static const int kRewards[4] = { 0x7A4, 0x7A5, 0x7A6, 0x7A7 };
    int old = self->state;
    if (newState == old) return;
    switch (old) {
    case 0:
        CALL(self, 8);
        break;
    case 1:
        if (self->owner && !self->flagAC)
            CALL(self->owner, 54);
        func_001854C8(D_0036C700, 0x5C, 0);
        break;
    case 2:
        break; /* the later states have no exit work */
    }
    self->state = newState;
    self->time = D_0036BB98.now;
    self->time2 = D_0036BB98.t40;
    switch (newState) {
    case 0:
        self->count = 0;
        CALL(self, 9);
        break;
    case 1:
        if (self->owner && !self->flagAC) {
            self->owner->field124 = func_0021A720(self);
            self->owner->field120 = 0;
            CALL(self->owner, 56);
        }
        func_001854C8(D_0036C700, 0x5B, 0);
        break;
    case 3: {
        Item *item = self->pairs[self->index].item;
        func_00262540(self->panel, kLabels[item->kind], D_00349370[self->index]);
        switch (item->kind) {
        case 2: {
            int n = ReadInt(D_00475480.keys[0], D_00468D30);
            WriteInt(D_00475480.keys[0], n + 1, D_00468D30);
            func_00262450(self->panel, 0x7AD);
            break;
        }
        case 3: {
            int n = ReadInt(D_00475480.keys[1], D_00468D30);
            WriteInt(D_00475480.keys[1], n + 1, D_00468D30);
            func_00262450(self->panel, 0x7AE);
            break;
        }
        }
        break;
    }
    case 4: {
        int gain;
        func_00262450(self->panel, kTitles[self->index]);
        gain = *(int *)((char *)self + self->index * 8 + 0x70);
        if (gain > 0) {
            func_00185328(D_0036C700, func_001852E0(D_0036C700) + gain);
            func_00262450(self->panel, kRewards[self->counter++]);
        }
        break;
    }
    case 7:
        if (!self->flagAC) func_002159D8(self->target, 2);
        break;
    case 8:
        if (!self->flagA8) func_001CFE08(D_00375290);
        if (!self->flagAC) func_002159D8(self->target, 2);
        func_001854C8(D_0036C700, 0x5D, self);
        self->count = 0;
        self->target = 0;
        break;
    }
    if (self->panel) {
        switch (self->state) {
        case -1:
        case 0:
        case 1:
        case 7:
        case 8:
            CALL(self->panel, 54);
            break;
        default:
            if (!func_00260758(self->panel, 0x37B)) {
                CALL(self->panel, 56);
                func_00262450(self->panel, 0x7A3);
            }
            break;
        }
    }
    int hi = self->state; /* separate reads keep the two bound tests unmerged */
    int lo = self->state;
    if (hi < 8 && lo >= 2) {
        if (!self->active) {
            int f = self->flags;
            if ((f ^ 1) & 1) *(int *)f |= 0x200;
            else self->flags = f | 0x200;
            func_001A93C8(&D_00475480, -1, 2);
            func_001A94A8(&D_00475480, -1);
            self->active = 1;
        }
    } else if (self->active) {
        int f = self->flags;
        if ((f ^ 1) & 1) *(int *)f &= ~0x200;
        else self->flags = f & ~0x200;
        func_001A94F0(&D_00475480, -1);
        func_001A9420(&D_00475480, -1, 2);
        self->active = 0;
    }
}
