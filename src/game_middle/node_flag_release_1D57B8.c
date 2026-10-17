// SLY3_CFLAGS: -Os -G0
extern char D_004BC230[];
extern void *D_004794C4;
struct ReleaseOwner {
    unsigned char prefix[0xC];
    void *node;
    unsigned char gap10[0x1C - 0x10];
    unsigned int flags;
};
void func_00283BB0(void *table, void *node, int first, int second);
void func_00187040(void *target);
void func_001D57B8(struct ReleaseOwner *owner)
{
    func_00283BB0(D_004BC230, owner->node, 0, -1);
    if (D_004794C4)
        func_00187040(D_004794C4);
    if (owner)
        owner->flags |= 2;
}
