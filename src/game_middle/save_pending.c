// SLY3_CFLAGS: -Os -G0
#include "eval_dispatch_api.h"

struct SavePendingView {
    unsigned char opaque00[8];
    int mode;
    unsigned char opaque0C[0x13950 - 12];
    void *selectedBlock;
    unsigned char opaque13954[4];
    void *pendingBlock;
};
struct MenuPendingView {
    unsigned char opaque00[0x58];
    int selection;
    unsigned char opaque5C[4];
    int action;
};
struct KEY;
extern unsigned char D_00375290[], D_003751D0[], D_00468D30[];
extern struct KEY *D_00479630;
CRef *func_002BC010(CRef *output, struct KEY *key, unsigned char *buffer);
void func_001D0C08(void *menu, int mode);
void func_001CFD80(void *save);

void func_001D1648(void)
{
    struct SavePendingView *save = (struct SavePendingView *)D_00375290;
    struct MenuPendingView *menu;
    CRef value;
    int enabled;
    if (save->mode != 6)
        return;
    menu = (struct MenuPendingView *)D_003751D0;
    if (menu->selection != 1)
        return;
    save->selectedBlock = save->pendingBlock;
    menu->action = 2;
    func_002BC010(&value, D_00479630, D_00468D30);
    enabled = value.payload.integer;
    func_0012BC20(&value);
    if (!enabled) {
        func_001D0C08(menu, 0x2F);
    } else {
        func_001D0C08(menu, 0x26);
        func_001CFD80(save);
    }
}
