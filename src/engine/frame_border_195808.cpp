// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
#include "../P2/gifs.h"
struct BorderColor { unsigned char r, g, b, a; };
struct BorderRect { int x0, y0, x1, y1; };
struct BorderConv { void *vtable; int widthSelector; int heightSelector; int unknownC; int divisor; };
extern BorderConv D_0036DBE0;
extern "C" {
int func_002BE320(BorderConv *conv, int value);
int func_002BE360(BorderConv *conv, int value);
int func_002BC668(BorderConv *conv, int value);
int func_002BC670(BorderConv *conv, int value);
}
extern "C" void func_00195808(BorderColor *color, BorderRect *rect, int flags, GIFS *gifs)
{
    ulong value;
    int column;
    int prim;
    if((signed char)color->a >= 0) prim = 0x46; else prim = 6;
    gifs->AddPrimPack(prim, 1, 0xE);
    gifs->PackAD(0x40, (long)rect->x0 | ((long)(rect->x1 - 1) << 16) | ((long)(rect->y0 / D_0036DBE0.divisor) << 32) | ((long)(rect->y1 / D_0036DBE0.divisor - 1) << 48));
    if(flags & 3) {
        gifs->PackAD(1, (ulong)color->r | ((ulong)color->g << 8) | ((ulong)color->b << 16) | ((ulong)color->a << 24));
        switch(flags) {
        case 1: value = 0x31001; break;
        case 2: value = 0x32001; break;
        case 3: value = 0x30000; break;
        }
        gifs->PackAD(0x47, value);
        gifs->PackAD(0x42, 0x44);
        for(column = rect->x0 & -0x20; column < rect->x1; column += 0x20) {
            long x = func_002BC668(&D_0036DBE0, func_002BE320(&D_0036DBE0, column));
            long y = func_002BC670(&D_0036DBE0, func_002BE360(&D_0036DBE0, rect->y0 / D_0036DBE0.divisor));
            gifs->PackAD(5, x | (y << 16));
            long x2 = func_002BC668(&D_0036DBE0, func_002BE320(&D_0036DBE0, column + 0x20));
            long y2 = func_002BC670(&D_0036DBE0, func_002BE360(&D_0036DBE0, rect->y1 / D_0036DBE0.divisor));
            gifs->PackAD(5, x2 | (y2 << 16));
        }
    }
    gifs->AddPrimEnd();
}
