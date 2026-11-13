// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
#include "../P2/gifs.h"

struct BarColorBytes { unsigned char r, g, b, a; };
struct BarColor {
    union { BarColorBytes bytes; unsigned int word; };
    BarColor() {}
    BarColor(const BarColor &v) { bytes = v.bytes; }
};
struct ProgressBar {
    unsigned char pad0[4];
    int total;
    int duration;
    int elapsed;
    unsigned char pad10[0x50 - 0x10];
    int state;
    BarColor frame, normal, warning, critical;
};
struct ScreenInfo { void *vtable; int width, height; };

extern "C" {
extern unsigned char D_0036DBE0[];
void func_00209798(BarColor color, GIFS *packets, float left, float top, float right, float bottom);
float func_0011ED10(float g);
void func_00196890(QW *chain);
}

extern "C" void func_001F9610(ProgressBar *bar)
{
    QW buffer[0x400];
    GIFS packets;
    packets.AllocStatic(0x400, buffer);
    packets.AddDmaCnt();
    int width = (int)((float)bar->duration * 620.0f / (float)bar->total);
    int elapsed = bar->elapsed;
    register int sh __asm__("$2") = ((ScreenInfo *)D_0036DBE0)->height; /* the one register pin: the original keeps the screen height in $v0 */
    int unit = 480 / sh;
    float six = 6.0f;
    __asm__("" : "+f"(six)); /* scheduling barrier on the height constant; emits no instruction */
    float height = (float)unit * six;
    int filled = (int)((float)width * ((float)(bar->duration - elapsed) / (float)bar->duration));
    float top = func_0011ED10((480.0f - (height + 32.0f)) / (float)unit) * (float)unit;
    float bottom = top + height;
    func_00209798(bar->frame, &packets, 10.0f, top, (float)(filled + 10), bottom);
    BarColor color;
    if (bar->state <= 0)
        color.bytes = bar->normal.bytes;
    else if (bar->state == 1)
        color.bytes = bar->warning.bytes;
    else
        color.bytes = bar->critical.bytes;
    func_00209798(color, &packets, (float)(filled + 10), top, (float)(width + 10), bottom);
    packets.AddPrimEnd();
    packets.AddDmaEnd();
    func_00196890(buffer);
}
