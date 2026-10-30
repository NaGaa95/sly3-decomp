// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// func_0019FF00 and func_001A01F8 share one .rodata section (two jump tables and the "%d" literal).
extern "C" {
#include "../../include/eval_dispatch_api.h"
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
struct CLOCK { float t; float dt; };
/* The option key pointer at 0x00479748 has no symbol of its own. */
struct OptionKeys { unsigned char pad[0x479748 - 0x479630]; KEY *key; };
extern "C" {
extern struct CLOCK g_clock;
extern unsigned char D_00475480[];
extern unsigned char D_00341FF0[];
extern unsigned char D_00468D30[];
extern unsigned char D_00474FF0[];
extern struct OptionKeys D_00479630;
float func_0011EE68(void *curve, float u);
char *func_00150630(void *game, int name);
void func_00271730(void *text, char *str);
void func_00271530(char *buf, int cb, const char *fmt, ...);
void func_002717E0(void *text, char *str);
void func_001A93C8(void *game, int a, int b);
void func_001A94A8(void *game, int a);
void func_001A9420(void *game, int a, int b);
void func_001A94F0(void *game, int a);
void func_00262450(void *self, int sound);
int func_0011E8F0(int lo, int hi);
void func_002485D8(void *audio, int id, int a, int b);
void func_0013BC80(void *self);
}
OptionReference WriteOption(KEY *, const OptionReference &, unsigned char *) __asm__("func_002BC050");
static inline void WriteRef(KEY *key, OptionReference ref, unsigned char *p)
{
    WriteOption(key, ref, p);
}
static inline void WriteInteger(KEY *key, int value, unsigned char *p)
{
    OptionReference ref(value);
    WriteRef(key, ref, p);
}
struct Slot { int sound; int sound2; int name; int value; };
struct Self {
    unsigned char pad[0x120]; int state; float start; int pad128; int name; int from; int to; int final;
    int a13C[5]; int a150[5]; int a164[5]; int a178[5]; struct Slot slots[8]; int pad20C; int slot; int a214[4]; int count; int pick;
};
extern "C" void func_0019FF00(struct Self *s, int state)
{
    int old = s->state;
    if (state == old) return;
    if (old == 0) {
        func_001A93C8(D_00475480, -1, 2);
        func_001A94A8(D_00475480, -1);
    }
    s->state = state;
    s->start = g_clock.t;
    switch (state) {
    case 1:
        s->slot = 0;
        break;
    case 5:
        s->slot++;
        break;
    case 2:
        func_00262450(s, s->slots[s->slot].sound);
        break;
    case 3:
        s->from = s->to;
        s->to = s->to + s->slots[s->slot].value;
        break;
    case 4:
        func_00262450(s, s->slots[s->slot].sound2);
        break;
    case 6:
        s->final = s->final + s->to;
        func_00262450(s, 0x40D);
        break;
    case 7:
        WriteInteger(D_00479630.key, s->final, D_00468D30);
        if (s->count > 0) {
            s->pick = s->a214[func_0011E8F0(0, s->count - 1)];
            func_002485D8(D_00474FF0, s->pick, 1, 0);
        } else {
            s->pick = -1;
        }
        func_00262450(s, 0x40C);
        break;
    case 9:
        func_0013BC80(s);
        break;
    case 0:
        func_001A9420(D_00475480, -1, 2);
        func_001A94F0(D_00475480, -1);
        break;
    }
}
extern "C" void func_001A01F8(void *text, int id, struct Self *s)
{
    char buf[8];
    int v;
    switch (id) {
    case 0x3F7:
        func_00271730(text, func_00150630(D_00475480, s->name));
        return;
    case 0x3F2:
        if (s->state == 3) {
            float u = func_0011EE68(D_00341FF0, (g_clock.t - s->start) * 0.5f);
            int a = s->from;
            int b = s->to;
            if (a == b) v = b;
            else if (a < b) v = a + (int)(u * ((float)b + 0.999f - (float)a));
            else v = b + (int)((1.0f - u) * ((float)a + 0.999f - (float)b));
        } else {
            v = s->to;
        }
        break;
    case 0x3F3:
        v = s->final;
        break;
    case 0x3F6:
        v = s->slots[s->slot].value;
        break;
    case 0x3F5:
        func_00271730(text, func_00150630(D_00475480, s->slots[s->slot].name));
        return;
    case 0x3F8: case 0x3F9: case 0x3FA: case 0x3FB: case 0x3FC:
        v = s->a13C[id - 0x3F8];
        break;
    case 0x3FD: case 0x3FE: case 0x3FF: case 0x400: case 0x401:
        v = s->a164[id - 0x3FD];
        break;
    case 0x402: case 0x403: case 0x404: case 0x405: case 0x406:
        v = s->a150[id - 0x402];
        break;
    case 0x407: case 0x408: case 0x409: case 0x40A: case 0x40B:
        v = s->a178[id - 0x407];
        break;
    default:
        return;
    }
    func_00271530(buf, sizeof buf, "%d", v);
    func_002717E0(text, buf);
}
