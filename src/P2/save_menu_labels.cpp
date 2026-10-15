// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
#include "game_text.h"

extern "C" unsigned char D_003751D0[], D_00475480[];
extern "C" int func_001D0D78(void *menu);

extern "C" void func_001D1AB0(unsigned short *output)
{
    switch (func_001D0D78(D_003751D0)) {
    case 1:
        func_002717E0(output, "&2S&.: ");
        func_00271780(output, func_00150630(D_00475480, 0x47));
        break;
    case 2:
    case 3:
        func_002717E0(output, "&2S&. : ");
        func_00271780(output, func_00150630(D_00475480, 0x45));
        func_00271828(output, "       ");
        func_00271780(output, func_00150630(D_00475480, 0x46));
        func_00271828(output, " : &2T&.");
        break;
    }
}
