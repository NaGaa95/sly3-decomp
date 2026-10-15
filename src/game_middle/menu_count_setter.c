// SLY3_CFLAGS: -Os -G0
struct MenuCountView {
    unsigned char opaque00[0x38];
    int count;
    float changed_at;
};
extern float D_0036BBD8;

void func_001D0D10(void *receiver, int count)
{
    struct MenuCountView *menu = (struct MenuCountView *)receiver;
    if (count != menu->count) {
        menu->count = count;
        menu->changed_at = D_0036BBD8;
    }
}
