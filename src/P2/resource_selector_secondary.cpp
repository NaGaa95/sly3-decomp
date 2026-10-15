// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
extern "C" {
int func_0025E150(void);

int func_001F5550(void *receiver, int selection)
{
    switch (selection) {
    case 12: return 0x204;
    case 0: return 0x22D;
    case 1: return 0x22B;
    case 4: return 0x229;
    case 5: return 0x22A;
    case 7: return 0x22C;
    case 8: return 0x227;
    default:
        switch (func_0025E150()) {
        case 0x21:
            switch (selection) {
            case 2: return 0x225;
            case 3: return 0x228;
            default: return -1;
            }
        case 0x24:
            switch (selection) {
            case 2: return 0x226;
            case 3: return 0x22E;
            default: return -1;
            }
        default: return -1;
        }
    }
}

int func_001F5648(void *receiver, int selection)
{
    switch (selection) {
    case 12: return 0x204;
    case 0: return 0x23E;
    case 1: return 0x23B;
    case 2: return 0x23C;
    case 3: return 0x239;
    case 4: return 0x23A;
    case 7: return 0x23D;
    default: return -1;
    }
}

int func_001F56B0(void *receiver, int selection)
{
    switch (selection) {
    case 12: return 0x204;
    case 0: return 0x24C;
    case 1: return 0x246;
    case 6: return 0x24A;
    case 9: return 0x24B;
    case 7: return 0x248;
    case 10: return 0x249;
    case 2:
    case 3:
    case 4: return 0x247;
    default: return -1;
    }
}
}
