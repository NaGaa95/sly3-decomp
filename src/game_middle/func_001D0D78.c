// SLY3_AS: gnu-2.9
// SLY3_CFLAGS: -Os -G0
struct MenuItem {
    unsigned char pad00[0x50];
    int type;
};
int func_001D0D78(struct MenuItem *item)
{
    switch (item->type) {
    case 0x1A:
    case 0x1C:
    case 0x1F:
    case 0x22:
    case 0x23:
    case 0x27:
    case 0x29:
    case 0x2F:
    case 0x30:
    case 0x31:
    case 0x3B:
        return 1;
    case 0x1D:
    case 0x20:
    case 0x28:
    case 0x2D:
        return 2;
    case 0x1B:
    case 0x24:
        return 3;
    }
    return 0;
}
