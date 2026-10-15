// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
extern "C" {
extern int D_0036DBE0;
int func_0025E150(void);

int func_001F53A8(void *receiver, int selection)
{
    switch (selection) {
    case 12: return 0x204;
    case 0: return 0x20E;
    case 1: return 0x20B;
    case 2: return 0x20D;
    case 3: return 0x20A;
    case 4: return 0x207;
    case 7: return 0x20C;
    case 8: return 0x208;
    default:
        const bool use_mode_resource = D_0036DBE0 == 2;
        if (use_mode_resource && selection == 5)
            return 0x206;
        if (func_0025E150() == 0x23 && selection == 5)
            return 0x209;
        return -1;
    }
}

int func_001F5470(void *receiver, int selection)
{
    switch (selection) {
    case 12: return 0x204;
    case 0: return 0x251;
    case 1: return 0x250;
    case 2: return 0x200;
    case 5: return 0x24D;
    case 7: return 0x24E;
    case 8: return 0x205;
    case 10: return 0x24F;
    default: return -1;
    }
}

int func_001F54E0(void *receiver, int selection)
{
    switch (selection) {
    case 12: return 0x204;
    case 0: return 0x237;
    case 1: return 0x238;
    case 2: return 0x200;
    case 4: return 0x235;
    case 5: return 0x234;
    case 7: return 0x236;
    case 10: return 0x202;
    default: return -1;
    }
}

}
