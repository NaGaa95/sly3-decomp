// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
#include "game_text.h"

extern "C" unsigned char D_0046F550[], D_00475480[];
extern "C" char D_00323DB0[];
extern "C" int func_001D45B0(void *menu);

extern "C" void func_001D1E60(unsigned short *output)
{
    switch (func_001D45B0(D_0046F550)) {
    case 0x25:
    case 0x2A:
    case 0x2B:
        func_00271730(output, func_00150630(D_00475480, 0x4F));
        func_00271828(output, D_00323DB0);
        func_00271828(output, "&2T&.");
        break;
    }
}
