// SLY3_CFLAGS: -Os -G0
#include "input_query_api.h"

extern unsigned char D_0036E740[];

unsigned int func_001A7980(int mask)
{
    unsigned char *input = D_0036E740;
    unsigned int first = func_001A7A80(input, (unsigned int)mask, 0.0f);
    unsigned int second = func_001A7A80(input + 0x11C0, (unsigned int)mask, 0.0f);
    return first | second;
}
