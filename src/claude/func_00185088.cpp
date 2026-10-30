// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
extern "C" {
#include "../../include/eval_dispatch_api.h"
}
class OptionReference {
public:
    CRef value;
    OptionReference(float real) { value.tag = 0x14; value.payload.real = real; }
    OptionReference(const OptionReference &) __asm__("func_0012AF00");
    void Drop() __asm__("func_0012BC20");
    ~OptionReference() { Drop(); }
};
struct KEY;
struct CLOCK { float t; float dt; };
struct LMR { float start, end; };
struct Timer { unsigned char pad[0x68]; float t; unsigned char pad6C[0xA8 - 0x6C]; float a8; unsigned char padAC[0xB8 - 0xAC]; LMR range; };
struct Game {
    unsigned char pad[0x4044]; Timer *timerA; int pad4048; Timer *timerB;
    unsigned char pad4050[0x406C - 0x4050]; KEY *key;
    unsigned char pad4070[0x4278 - 0x4070]; KEY *keys[9];
};
struct Slot { unsigned char pad[0x1050]; int state; unsigned char pad1054[0x1064 - 0x1054]; int level; unsigned char pad1068[0x11C0 - 0x1068]; };
extern "C" {
extern struct CLOCK g_clock;
extern Game D_00475480;
extern unsigned char D_00468D30[];
extern int D_0036DBE0;
extern Slot D_0036E740[2];
extern unsigned char D_0036BD20[];
int func_0025E188(void);
int func_0025E150(void);
void func_00171D98(void *p, float g);
}
OptionReference QueryOption(KEY *, unsigned char *) __asm__("func_002BC010");
OptionReference WriteOption(KEY *, const OptionReference &, unsigned char *) __asm__("func_002BC050");
static inline void WriteRef(KEY *key, OptionReference ref, unsigned char *p)
{
    WriteOption(key, ref, p);
}
static inline void WriteFloat(KEY *key, float value, unsigned char *p)
{
    OptionReference ref(value);
    WriteRef(key, ref, p);
}
static inline float ReadFloat(KEY *key, unsigned char *p)
{
    return QueryOption(key, p).value.payload.real;
}
static inline int Allowed() { return D_0036DBE0 != 2; }
static inline float Width(const LMR *p) { return p->end - p->start; }
static inline int Level(Slot *s)
{
    return s->state == 3 ? s->level : 10;
}
extern "C" void func_00185088(void)
{
    Game *game = &D_00475480;
    if (!game->key)
        return;
    {
        float g = ReadFloat(game->key, D_00468D30) + g_clock.dt;
        WriteFloat(game->key, g, D_00468D30);
    }
    int n = func_0025E188();
    if (Allowed() && func_0025E150() && n >= 0 && n < 9) {
        KEY *key = game->keys[n];
        if (key) {
            float g = ReadFloat(key, D_00468D30) + g_clock.dt;
            WriteFloat(key, g, D_00468D30);
        }
    }
    Slot *s0 = &D_0036E740[0];
    Slot *s1 = &D_0036E740[1];
    int a = Level(s0);
    int b = Level(s1);
    a = (a < b) ? a : b;
    if (a < 10) {
        Timer *ta = D_00475480.timerA;
        Timer *tb = D_00475480.timerB;
        if (ta) ta->a8 += g_clock.dt;
        if (tb) {
            LMR *r = &tb->range;
            tb->t += g_clock.dt;
            if (r->start < tb->t)
                func_00171D98(D_0036BD20, g_clock.dt / Width(r));
        }
    }
}
