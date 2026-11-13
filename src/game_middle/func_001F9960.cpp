// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_001F9960: render thread of the loading screen (Sly 2 func_001C9190 plus the Sly 3 status text): waits for the
// start semaphore, then draws the pulsing logo every frame (and, depending on the load state flags, a centred text line
// whose colour fades in with the logo alpha) until the frame-end semaphore is signalled.
// Matching notes: COLOR has a user copy constructor (memory-returned, byte copy = lwl/lwr) as in movie_render_packets.cpp;
// the colour lerp is the last TEXTBOX constructor argument (x/y are computed first); GClampR returns early (the
// assign-and-return clamp form swaps the alpha-byte registers).
#include "../P2/gifs.h"
#include "../P2/vifs.h"
struct SEMA { int count, maxCount, initialCount, waitThreads; uint attributes, option; };
struct M2 { float a[8]; M2() {} void Identity(); };
struct CLOCK { float t, dt; char pad8[0x40 - 0x8]; float frameT; };
struct LOADING { float tStart; int n4; int n8; };
struct FR { char pad0[0x24]; uchar *packet; char pad28[8]; int flags; };
struct RGBA { uchar r, g, b, a; };
struct LM { float gMin, gMax; };
struct COLOR {
    union { RGBA bytes; uint word; };
    COLOR() {}
    COLOR(uint value) { word = value; }
    COLOR(const COLOR &value) { bytes = value.bytes; }
};
struct TEXT { uchar opaque[0x180]; } __attribute__((aligned(16)));
struct TEXTBOX {
    float x, y, width, height;
    COLOR color;
    int horizontal, vertical;
    void SetPosition(float x, float y) __asm__("func_002BC878");
    void SetSize(float width, float height) __asm__("func_002BC888");
    void SetColor(COLOR *color) __asm__("func_002BC898");
    void SetHorizontal(int value) __asm__("func_002BC8B0");
    void SetVertical(int value) __asm__("func_002BC8B8");
    TEXTBOX(float x, float y, float width, float height, uint packed)
    {
        SetPosition(x, y);
        SetSize(width, height);
        COLOR color(packed);
        SetColor(&color);
        SetHorizontal(0);
        SetVertical(0);
    }
};
extern "C" {
extern int D_00467BE0, D_00467BE4, D_00467BE8, D_0036C684, D_0036C650, D_0036DCAC;
extern CLOCK D_0036BB98;
extern LOADING *D_0036AEB0;
extern int D_003470D0, D_003470D4, D_003470D8, D_003470DC;
extern float D_003470E0, D_003470E4, D_003470F0[3];
extern LM D_00341FF0;
extern GIFS D_0036C2E0;
extern VIFS D_0036C308;
extern FR *D_0036C328;
extern QW D_0036E340[], D_0036DCB0[];
extern uchar D_00389AB0[];
extern void *D_0036BF00;
int func_002936E0(int);
int func_002936C0(int);
int func_00293710(int, SEMA *);
float sinf(float);
void *func_00292034(void *, int, int);
void func_00165430(CLOCK *, int);
void func_001A77A0(void);
void func_00182C68(void);
void func_00182EE0(void);
void func_001F9FB0(GIFS *, M2 *, float);
char *func_0025E870(void *, int);
void func_00181330(TEXT *, char *, void *);
float func_00181A90(TEXT *, float);
float func_00181AD8(TEXT *);
void func_00181B60(TEXT *, TEXTBOX *, TEXTBOX *, GIFS *);
}
inline void M2::Identity() { func_00292034(this, 0, sizeof(*this)); a[0] = a[3] = 1.0f; }
static inline float GClampR(float g, float gMin, float gMax) { if (g < gMin) return gMin; if (gMax < g) return gMax; return g; }
static inline float GClamp(float g, const LM &lm) { return GClampR(g, lm.gMin, lm.gMax); }
static inline int NLerp(float g, int a, int b)
{
    if (a == b)
        return b;
    if (a < b)
        return a + (int)(g * ((float)b + 0.999f - (float)a));
    return b + (int)((1.0f - g) * ((float)a + 0.999f - (float)b));
}
static inline COLOR ColorLerp(float t, const COLOR &a, const COLOR &b)
{
    COLOR r;
    r.bytes.r = NLerp(t, a.bytes.r, b.bytes.r);
    r.bytes.g = NLerp(t, a.bytes.g, b.bytes.g);
    r.bytes.b = NLerp(t, a.bytes.b, b.bytes.b);
    r.bytes.a = NLerp(t, a.bytes.a, b.bytes.a);
    return r;
}
static inline void BeginFrame()
{
    func_00165430(&D_0036BB98, 1);
    func_001A77A0();
    func_00182C68();
    D_0036C328->packet = D_0036C308.m_pb;
    D_0036C308.AddDmaCall(D_0036E340);
    D_0036C308.AddDmaCnt();
    D_0036C308.AddVifDirect(D_0036DCAC, D_0036DCB0, 0);
    D_0036C308.EndDmaCnt();
}

extern "C" void func_001F9960(void *)
{
    SEMA status;
    M2 matrix;
    for (;;) {
        func_002936E0(D_00467BE0);
        for (;;) {
            BeginFrame();
            func_00293710(D_00467BE4, &status);
            if (status.count != 0)
                break;
            float t = D_0036BB98.frameT - D_0036AEB0->tStart;
            float scale = 1.0f + D_003470E0 * sinf(t * D_003470E4);
            matrix.Identity();
            matrix.a[0] = D_003470D0 * scale;
            matrix.a[3] = D_003470D4 * scale;
            matrix.a[4] = D_003470D8;
            matrix.a[5] = D_003470DC;
            float g = GClamp(D_003470F0[0] + t * (D_003470F0[1] + t * D_003470F0[2]), D_00341FF0);
            func_001F9FB0(&D_0036C2E0, &matrix, g);
            char *psz = 0;
            if (D_0036AEB0->n8 == 1 && D_0036AEB0->n4 != 1)
                psz = func_0025E870(D_00389AB0, 0x93);
            else if (D_0036AEB0->n4 == 1 && D_0036AEB0->n8 != 1)
                psz = func_0025E870(D_00389AB0, 0x94);
            if (psz && D_0036BF00) {
                TEXT text;
                func_00181330(&text, psz, D_0036BF00);
                float height = func_00181A90(&text, 480.0f);
                float width = func_00181AD8(&text);
                TEXTBOX box(D_003470D8 - width * 0.5f, D_003470DC + 70, width, height,
                            ColorLerp(g, COLOR(0x00C0C0C0), COLOR(0xFFC0C0C0)).word);
                TEXTBOX *pbox = &box;
                pbox->horizontal = 1;
                func_00181B60(&text, pbox, 0, &D_0036C2E0);
            }
            func_00182EE0();
            D_0036C650++;
        }
        D_0036C328->flags &= ~1;
        func_00182EE0();
        D_0036C650++;
        do {
            func_00293710(D_0036C684, &status);
        } while (status.count == 0);
        func_002936E0(D_00467BE4);
        func_002936C0(D_00467BE8);
    }
}
