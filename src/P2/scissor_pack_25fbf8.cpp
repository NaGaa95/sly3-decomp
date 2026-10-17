// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "gifs.h"
struct COORDINATE_CONVERSION_FIELDS;
struct ScreenExtentPrefix {
    int mode, width, height;
};
struct ScissorRect {
    int left, top, right, bottom;
};
extern "C" {
extern unsigned char D_0036DBE0[];
int func_002BC640(COORDINATE_CONVERSION_FIELDS *, int);
int func_002BC648(COORDINATE_CONVERSION_FIELDS *, int);
}
extern "C" void func_0025FBF8(ScissorRect *rect, int count, QW *storage)
{
    GIFS packets;
    packets.AllocStatic(count, storage);
    packets.AddPrimPack(0, 1, 0xE);
    ScreenExtentPrefix *screen = (ScreenExtentPrefix *)D_0036DBE0;
    int left = func_002BC640((COORDINATE_CONVERSION_FIELDS *)screen, rect->left * screen->width / 640);
    int right = func_002BC640((COORDINATE_CONVERSION_FIELDS *)screen, rect->right * screen->width / 640);
    int top = func_002BC648((COORDINATE_CONVERSION_FIELDS *)screen, rect->top * screen->height / 480);
    int bottom = func_002BC648((COORDINATE_CONVERSION_FIELDS *)screen, rect->bottom * screen->height / 480);
    long data = left | ((long)(right - 1) << 16) | ((long)top << 32) | ((long)(bottom - 1) << 48);
    packets.PackAD(0x40, data);
    packets.AddPrimEnd();
}
