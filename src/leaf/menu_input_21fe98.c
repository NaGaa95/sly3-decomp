// Per-frame input handling of the unlock menu: close on cancel, on confirm either play the error sound, spend the unlock cost and refresh, or forward the purchase result, then update the open dialog.
// SLY3_CFLAGS: -Os -G0
struct Row {
    unsigned char opaque00[8];
    int cost;
    unsigned char opaque0C[0x3C - 0xC];
};
struct Menu {
    unsigned char opaque00[0x1C];
    void *controller;
    unsigned char opaque20[0x40 - 0x20];
    int open;
    unsigned char opaque44[0x50 - 0x44];
    int state;
    unsigned char opaque54[0x27C - 0x54];
    int selection;
};
extern struct Row D_00343098[];
extern unsigned char D_0036C700[];
void func_0021EBE0(struct Menu *menu);
int func_0021FE60(struct Menu *menu);
int func_001A7A80(void *controller, int button, float hold);
int func_001A7AE0(void *controller, int button, int frames);
void func_00220590(struct Menu *menu, int mode);
int func_001852E0(void *context);
void func_00185328(void *context, int value);
void func_0021ED28(struct Menu *menu, int a, int b);
void func_0021F5D0(int selection, int value);
void func_002201D8(struct Menu *menu);
void func_0021EC30(struct Menu *menu);
void func_002202A0(struct Menu *menu);
void *func_002459F8(int id);
void func_00244F08(void *sound, int mode);
void func_0021FE98(struct Menu *menu)
{
    func_0021EBE0(menu);
    if (menu->state == -1) return;
    if (!menu->controller) return;
    if (!func_0021FE60(menu)) return;
    if (menu->open) {
        if (func_001A7A80(menu->controller, 0x10, 0.0f) || func_001A7AE0(menu->controller, 0x100, 8)) {
            func_00220590(menu, -1);
            return;
        }
    }
    if (menu->state == 0) {
        if (func_001A7A80(menu->controller, 0x40, 0.0f)) {
            if (menu->selection == -1) {
                func_00244F08(func_002459F8(0x36), 0);
            } else {
                int cost = D_00343098[menu->selection].cost;
                int money = func_001852E0(D_0036C700);
                if (!menu->open) {
                    func_0021ED28(menu, -1, -1);
                    func_00185328(D_0036C700, money - cost);
                    func_0021F5D0(menu->selection, 1);
                    func_002201D8(menu);
                    func_00244F08(func_002459F8(0x29), 0);
                } else if (money >= cost)
                    func_0021ED28(menu, 0, 0x43);
                else
                    func_0021ED28(menu, 1, 0x44);
            }
        }
    }
    if (!menu->open) {
        if (func_001A7A80(menu->controller, 0x10, 0.0f))
            func_0021ED28(menu, -1, -1);
    }
    if (menu->open)
        func_0021EC30(menu);
    func_002202A0(menu);
}
