// SLY3_CFLAGS: -Os -G0
struct Subject {
    unsigned char prefix[0x130];
    int selector;
    unsigned char gap[0x180 - 0x134];
    int override;
};
extern char D_00475480[];
int func_001A9478(void *, int);
int func_001A9600(void *, int);
int func_001F42E8(struct Subject *subject)
{
    if (!subject->override) {
        if (!func_001A9478(D_00475480, subject->selector) || func_001A9600(D_00475480, subject->selector))
            return 0;
    }
    return 1;
}
