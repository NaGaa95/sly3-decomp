// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "gifs.h"
struct CFont;
class CTextBox;
struct COORDINATE_CONVERSION_FIELDS;
struct ScreenExtentPrefix {
    int mode, width, height;
};
extern "C" {
extern unsigned char D_0036DBE0[];
int func_002BC640(COORDINATE_CONVERSION_FIELDS *, int);
int func_002BC648(COORDINATE_CONVERSION_FIELDS *, int);
}
extern "C" void func_001808E0(CFont *, CTextBox *clip, GIFS *packets)
{
    if (!clip)
        return;
    packets->AddPrimPack(0, 1, 0xE);
    ScreenExtentPrefix *screen=(ScreenExtentPrefix *)D_0036DBE0;
    int width=func_002BC640((COORDINATE_CONVERSION_FIELDS *)screen, screen->width);
    int height=func_002BC648((COORDINATE_CONVERSION_FIELDS *)screen, screen->height);
    ulong data=((ulong)(width-1)<<16)|((ulong)(height-1)<<48);
    packets->PackAD(0x40, data);
}
