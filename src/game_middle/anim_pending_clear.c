// SLY3_CFLAGS: -Os -G0
struct AnimOwner {
    unsigned char prefix[0x1C9C];
    int request;
    unsigned char gap[0x1CA8 - 0x1CA0];
    void *animation;
};
extern char D_00475480[];
int func_00138AC8(void *);
int func_001A9478(void *, int);
void func_001E4A20(void *, int);
void func_001DD858(struct AnimOwner *owner)
{
    if (owner->request) {
        if (!owner->animation || func_00138AC8(owner->animation) || func_001A9478(D_00475480, -1))
            func_001E4A20(owner, 0);
    }
}
