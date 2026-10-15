// SLY3_CFLAGS: -Os -G0
#include "output_types.h"

int func_00271490(char *destination, unsigned int capacity, const char *format, char *arguments)
{
    struct Output output;
    int length;
    func_0025A210(&output, destination, capacity, 0);
    length = func_00271008(&output, format, arguments);
    if ((unsigned int)length >= capacity) {
        destination[capacity - 1] = 0;
        length = -1;
    } else {
        destination[length] = 0;
    }
    func_0025A288(&output, 2);
    return length;
}
