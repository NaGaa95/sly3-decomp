// SLY3_CFLAGS: -Os -G0
struct ActionOwnerView {
    char prefix[0x1460];
    void *control;
};
extern int D_0036DBE0;
int func_001F5020(void *receiver, int selector)
{
    struct ActionOwnerView *p = (struct ActionOwnerView *)receiver;
    switch (selector) {
    case 12: return 0x204;
    case 0: return 0x257;
    case 2: return 0x200;
    case 3: return 0x252;
    case 4: return 0x253;
    case 8: return 0x205;
    }
    if (p->control) {
        switch (selector) {
        case 6: return 0x24A;
        case 9: return 0x24B;
        case 5:
        case 11: return -1;
        }
    }
    if ((D_0036DBE0 ^ 2) == 0) {
        switch (selector) {
        case 1: return 0x259;
        case 5: return 0x206;
        case 7: return 0x255;
        case 10: return 0x203;
        case 6:
        case 9: return -1;
        }
    } else {
        switch (selector) {
        case 1: return 0x258;
        case 5:
        case 6:
        case 9: return 0x206;
        case 7: return 0x254;
        case 10: return 0x202;
        case 11: return 0x201;
        }
    }
    return -1;
}
