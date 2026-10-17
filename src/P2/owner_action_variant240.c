// SLY3_CFLAGS: -Os -G0
struct ActionOwnerView {
    char prefix[0x1460];
    void *control;
};
int func_001F5178(void *receiver, int selector)
{
    struct ActionOwnerView *p = (struct ActionOwnerView *)receiver;
    switch (selector) {
    case 12: return 0x204;
    case 0: return 0x214;
    case 1: return 0x215;
    case 2: return 0x200;
    case 3: return 0x20F;
    case 4: return 0x210;
    case 7: return 0x211;
    case 8: return 0x213;
    case 10: return 0x212;
    }
    if (p->control) {
        switch (selector) {
        case 6: return 0x24A;
        case 9: return 0x24B;
        default: return -1;
        }
    }
    switch (selector) {
    case 5: return 0x206;
    case 6: return 0x206;
    case 9: return 0x206;
    case 11: return 0x201;
    }
    return -1;
}
