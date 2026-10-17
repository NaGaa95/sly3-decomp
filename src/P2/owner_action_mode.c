// SLY3_CFLAGS: -Os -G0
extern int D_0036DBE0;
int func_001F52F0(void *receiver, int selector)
{
    switch (selector) {
    case 12: return 0x204;
    case 0: return 0x220;
    case 1: return 0x21B;
    case 2: return 0x200;
    case 4: return 0x21C;
    case 3: return 0x21F;
    case 8: return 0x21A;
    case 10: return 0x203;
    }
    if ((D_0036DBE0 ^ 2) == 0) {
        switch (selector) {
        case 5: return 0x206;
        case 7: return 0x21E;
        }
    } else if (selector == 7) {
        return 0x21D;
    }
    return -1;
}
