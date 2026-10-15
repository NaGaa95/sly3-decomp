// Format every selected mask through the original style-tagged byte string.
// Each conversion replaces the sixteen-bit destination. When no mask is
// selected, the destination is left untouched. Names describe consumed fields.
// SLY3_CFLAGS: -Os -G0
#include "mask_formatter_data.h"
struct MASK_CHARACTER_RECEIVER {
    int unknown0;
    int unknown4;
    unsigned int flags;
};
int func_00271448(char *destination, const char *format, ...);
unsigned short *func_002717E0(unsigned short *destination, const char *source);
void func_0027EEC8(struct MASK_CHARACTER_RECEIVER *receiver, unsigned short *destination) {
    struct MASK_CHARACTER_TABLE table = D_003294A8;
    char text[32];
    unsigned int i;
    for (i = 0; i < 16; ++i) {
        if (receiver->flags & table.records[i].mask) {
            func_00271448(text, D_00329528, table.records[i].character);
            func_002717E0(destination, text);
        }
    }
}
