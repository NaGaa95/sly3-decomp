// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
struct RGBA { unsigned char r, g, b, a; };
struct COLOR {
    union { RGBA bytes; unsigned int word; };
    COLOR() {}
    COLOR(unsigned int value) { word = value; }
    COLOR(const COLOR &value) { bytes = value.bytes; }
};
struct RECTI { int x0, y0, x1, y1; };
struct LM { float lo, hi; };
struct BOX {
    float x, y, width, height;
    COLOR color;
    int horizontal, vertical;
    void SetPosition(float x, float y) __asm__("func_002BC878");
    void SetSize(float width, float height) __asm__("func_002BC888");
    void SetColor(COLOR *color) __asm__("func_002BC898");
    void SetHorizontal(int value) __asm__("func_002BC8B0");
    void SetVertical(int value) __asm__("func_002BC8B8");
    BOX(const RECTI &rect, unsigned int packed, int horizontal, int vertical) {
        SetPosition((float)rect.x0, (float)rect.y0);
        SetSize((float)(rect.x1 - rect.x0), (float)(rect.y1 - rect.y0));
        COLOR color(packed);
        SetColor(&color);
        SetHorizontal(horizontal);
        SetVertical(vertical);
    }
};
struct FONT { char opaque[0x1B0]; };
struct CLOCK { float t, dt; char pad8[0x40 - 8]; float tReal; };
struct OBJ { char pad[0x1050]; int state; char pad1054[4]; float tState; };
struct MGR { char pad[0x4334]; int active; };
extern "C" {
extern int D_0036DBE0;
extern MGR D_00475480;
extern OBJ D_0036E740;
extern CLOCK g_clock;
extern COLOR D_0036E6C0;
extern int D_0036E6C4;
extern COLOR D_0036E6C8;
extern int D_0036E6CC;
int func_001A9478(void *manager, int index);
int func_0025E150(void);
char *func_00165B28(void *manager);
char *func_001A91D8(OBJ *p);
void *func_00150630(void *manager, int id);
float cosf(float);
void *func_00264880(FONT *font, void *text, float scale);
void func_00265480(FONT *font, BOX *box, int layer);
}
static inline bool IsMode() { return D_0036DBE0 == 2; }
static inline int NLerp(float g, int a, int b)
{
    if (a == b)
        return b;
    if (a < b)
        return a + (int)(g * ((float)b + 0.999f - (float)a));
    return b + (int)((1.0f - g) * ((float)a + 0.999f - (float)b));
}
static inline COLOR ColorLerp(float t, COLOR a, COLOR b)
{
    COLOR r;
    r.bytes.r = NLerp(t, a.bytes.r, b.bytes.r);
    r.bytes.g = NLerp(t, a.bytes.g, b.bytes.g);
    r.bytes.b = NLerp(t, a.bytes.b, b.bytes.b);
    r.bytes.a = NLerp(t, a.bytes.a, b.bytes.a);
    return r;
}
extern "C" void func_001A8188(OBJ *p)
{
    LM range;
    RECTI rect;
    if (!IsMode())
        return;
    if (!D_00475480.active)
        return;
    if (func_001A9478(&D_00475480, -1))
        return;
    if (g_clock.dt <= 0.0f)
        return;
    if (p->state != 1)
        return;
    if (g_clock.tReal - p->tState <= 0.5f)
        return;
    if (func_0025E150() == 0x16) {
        range.lo = 0.5f;
        range.hi = 0.7f;
        rect = *(RECTI *)(func_00165B28(&D_00475480) + 0x150);
        rect.y1 -= (rect.y1 - rect.y0) / 2;
        if (p == &D_0036E740)
            rect.x1 -= (rect.x1 - rect.x0) / 2;
        else
            rect.x0 += (rect.x1 - rect.x0) / 2;
    } else {
        range.lo = 0.6f;
        range.hi = 0.8f;
        rect = *(RECTI *)(func_001A91D8(p) + 0x150);
    }
    if (!D_0036E6C4) {
        D_0036E6C0.word = 0xFF008080;
        D_0036E6C4 = 1;
    }
    if (!D_0036E6CC) {
        D_0036E6C8.word = 0xFF000080;
        D_0036E6CC = 1;
    }
    void *text = func_00150630(&D_00475480, 0x12);
    float t = cosf(g_clock.tReal * 7.0f) * 0.5f + 0.5f;
    float scale = (1.0f - t) * range.lo + t * range.hi;
    COLOR color = ColorLerp(t, D_0036E6C0, D_0036E6C8);
    FONT font;
    func_00264880(&font, text, scale);
    BOX box(rect, color.word, 1, 1);
    func_00265480(&font, &box, 0x18);
}
