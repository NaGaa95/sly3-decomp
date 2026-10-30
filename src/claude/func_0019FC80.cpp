// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
extern "C" {
#include "../../include/eval_dispatch_api.h"
}
class OptionReadReference {
public:
    CRef value;
    OptionReadReference(const OptionReadReference &) __asm__("func_0012AF00");
    void Drop() __asm__("func_0012BC20");
    ~OptionReadReference() { Drop(); }
};
struct KEY;
struct CLOCK { float t; float dt; };
/* The option key pointer at 0x00479748 has no symbol of its own. */
struct OptionKeys { unsigned char pad[0x479748 - 0x479630]; KEY *key; };
struct VTE { short delta; short pad; void (*pfn)(void *); };
struct Slot { int sound; int sound2; int name; int value; };
struct Self {
    unsigned char pad0[0xC]; struct VTE *pvt; unsigned char pad10[0x48 - 0x10]; int n48;
    unsigned char pad4C[0x120 - 0x4C]; int state; float start; int f128; int name; int from; int to; int final;
    int a13C[5]; int a150[5]; int a164[5]; int a178[5]; struct Slot slots[8]; int count; int slot; int a214[4]; int n224; int pick;
};
extern "C" {
extern struct CLOCK g_clock;
extern unsigned char D_00468D30[];
extern unsigned char D_00474FF0[];
extern struct OptionKeys D_00479630;
OptionReadReference QueryReadOption(KEY *, unsigned char *) __asm__("func_002BC010");
void func_00261250(struct Self *s);
int func_00260758(struct Self *s, int sound);
int func_00260738(struct Self *s);
int func_001A01A0(struct Self *s);
int func_00248858(void *p, int n);
void func_0019FF00(struct Self *s, int state);
}
static inline int ReadInteger(KEY *key)
{
    return QueryReadOption(key, D_00468D30).value.payload.integer;
}
extern "C" void func_0019FC80(struct Self *s)
{
    int st;
    func_00261250(s);
    do {
        st = s->state;
        switch (st) {
        case 0:
            break;
        case 1:
            if (s->n48 != 3) {
                if (s->slot < s->count) func_0019FF00(s, 2);
                else func_0019FF00(s, 6);
            }
            break;
        case 2:
            if (!func_00260758(s, s->slots[s->slot].sound)) func_0019FF00(s, 3);
            break;
        case 3:
            if (g_clock.t - s->start > 2.0f || func_001A01A0(s)) {
                if (s->slot + 1 < s->count) func_0019FF00(s, 4);
                else func_0019FF00(s, 6);
            }
            break;
        case 4:
            if (!func_00260758(s, s->slots[s->slot].sound2)) func_0019FF00(s, 5);
            break;
        case 5:
            if (s->slot < s->count) func_0019FF00(s, 2);
            else func_0019FF00(s, 6);
            break;
        case 6:
            if (!func_00260758(s, 0x40D)) {
                if (s->f128 && ReadInteger(D_00479630.key) < s->final) func_0019FF00(s, 7);
                else func_0019FF00(s, 8);
            }
            break;
        case 7:
            if (!func_00260758(s, 0x40C)) {
                if (s->pick == -1 || !func_00248858(D_00474FF0, s->pick)) func_0019FF00(s, 8);
            }
            break;
        case 8:
            if (func_001A01A0(s)) s->pvt[0x36].pfn((char *)s + s->pvt[0x36].delta);
            break;
        case 9:
            if (func_00260738(s)) func_0019FF00(s, 0);
            break;
        }
    } while (s->state != st);
}
