// Format the resource name in its original local buffer, resolve it, and return the selected update result.

// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions

// Original EE call/control flow reconstructed with physical-register arguments.

#include "m2c_prelude.h"



M2C_UNK func_001CFB40(s32, s32, void *);                      /* extern */

#include "card_transfer_api.h"

M2C_UNK func_001D08C8(s32, s32);                    /* extern */

s32 func_001D09C8(s32, void *, s32, M2C_UNK);       /* extern */



s32 func_001D0508(s32 arg0, s32 arg1) {

    char buffer[80];

    s32 sp50;

    s32 result;



    func_001CFB40(arg0, arg1, buffer);

    sp50 = -1;

    if (func_001D0860((void *)arg0, buffer, 1, &sp50) != 0) {

        result = func_001D09C8(arg0, buffer, arg1, 0x6808);

    } else {

        func_001D08C8(arg0, sp50);

        result = 0;

    }

    return result;

}

