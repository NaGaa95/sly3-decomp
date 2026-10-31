// Store a new mode value and restamp the change time with the global clock when the value differs.
// SLY3_CFLAGS: -Os -G0
struct ModeView {
    char opaque00[0x38];
    int mode;
    float changed_at;
};
extern float D_0036BBD8;

void func_00221A58(struct ModeView *view, int mode)
{
    if (mode != view->mode) {
        view->mode = mode;
        view->changed_at = D_0036BBD8;
    }
}
