// SLY3_CFLAGS: -Os -G0
struct ResetControl {
    unsigned char prefix[0x1488];
    int state;
    int value;
    int extra;
};
struct ResetWorld {
    unsigned char prefix[0x4044];
    void *child;
};
extern struct ResetControl D_0036C700;
extern struct ResetWorld D_00475480;
int func_0025E188(void);
void *func_0025E070(int id);
void func_00289070(void *world, void *record, int id, int option, int selection);
void func_00187040(void *child);
void func_001D5598(unsigned int *flags)
{
    if (D_0036C700.state == -1) {
        if (func_0025E188() == 2) {
            D_0036C700.state = 1;
            D_0036C700.value = func_0025E188();
        } else {
            D_0036C700.state = 6;
            D_0036C700.value = func_0025E188();
            D_0036C700.extra = 0;
        }
    }
    func_00289070(&D_00475480, func_0025E070(0), 0x1A8, 0, -1);
    if (D_00475480.child)
        func_00187040(D_00475480.child);
    if (flags)
        flags[7] |= 2;
}
