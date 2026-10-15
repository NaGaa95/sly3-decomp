// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
#include "game_text.h"

extern "C" {
extern unsigned char D_0046FC30[], D_00375290[], D_00468D30[], D_004BC268[];
extern unsigned char D_00475480[];
int func_0021DD30(void *menu);
int func_001CFDF8(void *save);
int func_0025E198(void *record);
int func_00222410(int index);
int func_0025E6D0(void *record);
int func_00271448(char *output, const char *format, ...);
}

extern "C" void func_001D1BF0(unsigned short *output)
{
    void *record;
    char text[32];
    if (func_0021DD30(D_0046FC30))
        return;
    if (func_001CFDF8(D_00375290))
        record = D_004BC268;
    else
        record = D_00468D30;
    func_00271730(output, func_00150630(D_00475480,
        func_00222410(func_0025E198(record))));
    func_00271828(output, " : ");
    func_00271448(text, "%d%%", func_0025E6D0(record));
    func_00271828(output, text);
}
