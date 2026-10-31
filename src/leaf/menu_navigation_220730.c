// Record a new navigation state and step the selection one entry up (states 1-3) or down (states 5-7), playing the move or limit sound.
// SLY3_CFLAGS: -Os -G0
struct MenuView {
    unsigned char opaque00[0x38];
    int navigation;
    float changedAt;
    unsigned char opaque40[0x58 - 0x40];
    int count;
    unsigned char opaque5C[0x274 - 0x5C];
    int index;
};
extern float D_0036BBD8;
void func_002200B8(struct MenuView *menu, int index);
void *func_002459F8(int identifier);
void func_00244F08(void *sound, int mode);

void func_00220730(struct MenuView *menu, int navigation)
{
    if (navigation == menu->navigation) return;
    menu->navigation = navigation;
    menu->changedAt = D_0036BBD8;
    switch (navigation) {
    case 1:
    case 2:
    case 3:
        if (menu->index > 0) {
            func_002200B8(menu, menu->index - 1);
            func_00244F08(func_002459F8(0x35), 0);
        } else {
            func_00244F08(func_002459F8(0x36), 0);
        }
        break;
    case 5:
    case 6:
    case 7:
        if (menu->index < menu->count - 1) {
            func_002200B8(menu, menu->index + 1);
            func_00244F08(func_002459F8(0x35), 0);
        } else {
            func_00244F08(func_002459F8(0x36), 0);
        }
        break;
    }
}
