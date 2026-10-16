// SLY3_CFLAGS: -Os -G0
extern char D_0036BB98[];
extern char D_00475480[];
extern char D_0036C700[];
struct MenuView { unsigned char opaque[0x38]; int state38; };
int func_0021DD30(void *menu);
void func_0021DE60(void *menu);
void func_00165548(void *clock, int channel, float scale);
void func_001A9420(void *unused, int selection, unsigned int flags);
void func_001854C8(void *context, int event, void *owner);
void func_001D2DF8(void *receiver)
{
    struct MenuView *menu = (struct MenuView *)receiver;
    if (func_0021DD30(receiver)) {
        menu->state38 = 0;
        func_00165548(D_0036BB98, 0, 1.0f);
        func_001A9420(D_00475480, -1, 0);
        func_001854C8(D_0036C700, 0x3E, 0);
        func_0021DE60(receiver);
    }
}
