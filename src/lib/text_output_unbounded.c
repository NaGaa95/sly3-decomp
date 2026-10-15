// SLY3_CFLAGS: -Os -G0
#include "output_types.h"

int func_002713D0(void *destination, char *format, char *arguments)
{
    struct Output output;
    int length;
    char *text = (char *)destination;
    func_0025A210(&output, destination, 0, 0);
    length = func_00271008(&output, format, arguments);
    text[length] = 0;
    func_0025A288(&output, 2);
    return length;
}
