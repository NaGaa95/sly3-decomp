// The formatter visits these flag/character records in this exact order.
// Its fixed %c style string is converted to the game's sixteen-bit characters.
// SLY3_CFLAGS: -Os -G0
#include "mask_formatter_data.h"

const struct MASK_CHARACTER_TABLE D_003294A8 = {{
    {1u << 6, 'X'},
    {1u << 5, 'O'},
    {1u << 4, 'T'},
    {1u << 7, 'S'},
    {1u << 11, '!'},
    {1u << 8, '_'},
    {1u << 12, '^'},
    {1u << 14, 'v'},
    {1u << 15, '<'},
    {1u << 13, '>'},
    {1u << 2, 'L'},
    {1u << 0, 'l'},
    {1u << 9, '('},
    {1u << 3, 'R'},
    {1u << 1, 'r'},
    {1u << 10, ')'}
}};
const char D_00329528[7] = "&2%c&.";
