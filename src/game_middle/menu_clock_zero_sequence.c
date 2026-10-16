// SLY3_CFLAGS: -Os -G0
extern char D_0036BB98[];
extern char D_00475480[];
extern char D_0036C700[];
void func_0021DDC0(void *panel, int selection);
int func_0025E150(void);
void func_00165548(void *clock, int channel, float scale);
void func_001A93C8(void *unused, int selection, unsigned int flags);
void func_001854C8(void *context, int event, void *owner);
void func_001D2D90(void *menu, int selection)
{
    func_0021DDC0(menu, selection);
    if (func_0025E150() != 1)
        func_00165548(D_0036BB98, 0, 0.0f);
    func_001A93C8(D_00475480, -1, 0);
    func_001854C8(D_0036C700, 0x3A, 0);
}
