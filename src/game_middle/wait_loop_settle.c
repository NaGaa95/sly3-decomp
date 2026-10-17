// SLY3_CFLAGS: -Os -G0
struct WaitOwner {
    unsigned char prefix[0x30];
    int pending;
};
void func_002389A0(void *);
int func_00238AA8(void *);
int func_00238AD0(void *);
void func_001A5810(void *, int);
void func_001A56E0(struct WaitOwner *owner)
{
    int previous;
    func_002389A0(owner);
    while (!func_00238AA8(owner)) {
        previous = owner->pending;
        if (previous == 0 && func_00238AD0(owner))
            func_001A5810(owner, -1);
        if (previous == owner->pending)
            break;
    }
}
