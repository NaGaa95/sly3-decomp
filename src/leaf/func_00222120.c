// Store a new count value and restamp the change time with the global clock when the value differs.
// SLY3_CFLAGS: -Os -G0
struct CountView {
    unsigned char opaque00[0x38];
    int count;
    float changed_at;
};
extern float D_0036BBD8;

void func_00222120(struct CountView *view, int count)
{
    if (count != view->count) {
        view->count = count;
        view->changed_at = D_0036BBD8;
    }
}
