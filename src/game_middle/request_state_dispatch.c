// SLY3_CFLAGS: -Os -G0
struct RequestOwner {
    unsigned char prefix[0x1520];
    int state;
};
void func_00154750(void);
unsigned int func_00154798(void *, int);
void func_001E2E88(void *, int);
void func_001E2710(struct RequestOwner *owner)
{
    func_00154750();
    if (!func_00154798(owner, 0x11)) {
        if (owner->state == 0x16)
            func_001E2E88(owner, 2);
    }
}
