// SLY3_CFLAGS: -Os -G0
struct MenuSelectionView {
    unsigned char opaque00[0x38];
    int selection;
    float changedAt;
};
extern float D_0036BBD8;

void func_001D2208(void *receiver, int selection)
{
    struct MenuSelectionView *menu = receiver;
    if (selection != menu->selection) {
        menu->selection = selection;
        menu->changedAt = D_0036BBD8;
    }
}
