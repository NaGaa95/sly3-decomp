// SLY3_CFLAGS: -Os -G0
struct SelectionClock { float time; };
struct SelectionView {
    unsigned char prefix[0x190];
    int selection;
    float changed;
    unsigned char gap198[0x3C0 - 0x198];
    int word3C0;
};
extern struct SelectionClock D_0036BB98;
extern unsigned char D_00475480[];
void func_001A9420(void *unused, int selection, unsigned int flags);
void func_001A93C8(void *unused, int selection, unsigned int flags);
void func_0020A6D0(struct SelectionView *view, int selection)
{
    if (view->selection == selection)
        return;
    if (view->selection == 1)
        func_001A9420(D_00475480, -1, 3);
    view->selection = selection;
    view->changed = D_0036BB98.time;
    view->word3C0 = 0;
    if (selection == 1)
        func_001A93C8(D_00475480, -1, 3);
}
