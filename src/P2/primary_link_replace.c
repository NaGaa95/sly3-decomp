// SLY3_CFLAGS: -Os -G0
#include "owner_parent_link.h"
struct BorrowedLink {
    unsigned char prefix[0x124];
    int ownerSlot;
};
struct PrimaryLinkOwner {
    unsigned char prefix[0x144];
    struct BorrowedLink *link;
};
void func_00273ED0(void *, void *, void *, int);
void func_00273E48(void *, void *, void *, int);
void func_001F4748(struct PrimaryLinkOwner *owner, struct BorrowedLink *replacement)
{
    if (replacement == owner->link)
        return;
    if (owner->link)
        func_00273ED0(owner->link, 0, owner, 1);
    owner->link = replacement;
    if (replacement) {
        replacement->ownerSlot = -1;
        func_001C7A00(owner->link, 0, 0);
        func_00273E48(owner->link, 0, owner, 1);
    }
}
