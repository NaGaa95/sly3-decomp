// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
int func_001C8768(void *receiver, int identifier);

int func_001F4F40(void *receiver, int selector) {
    if (func_001C8768(receiver, 0x7D3)) {
        switch (selector) {
        case 0: return 0x219;
        case 2: return 0x217;
        case 7: return 0x218;
        case 4:
        case 8: return 0x216;
        case 12: return 0x204;
        }
    }
    if (func_001C8768(receiver, 0x7D4)) {
        switch (selector) {
        case 0: return 0x221;
        case 2: return 0x222;
        case 1: return 0x223;
        case 7: return 0x224;
        case 12: return 0x204;
        }
    }
    return -1;
}
