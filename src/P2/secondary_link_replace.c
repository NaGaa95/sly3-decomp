// SLY3_CFLAGS: -Os -G0
struct SecondaryLinkOwner {
    unsigned char prefix[0x148];
    void *link;
};
void func_00273ED0(void *, void *, void *, int);
void func_00273E48(void *, void *, void *, int);
void func_001F47C8(struct SecondaryLinkOwner *owner, void *replacement)
{
    if (replacement == owner->link)
        return;
    if (owner->link)
        func_00273ED0(owner->link, 0, owner, 1);
    owner->link = replacement;
    if (replacement)
        func_00273E48(replacement, 0, owner, 1);
}
