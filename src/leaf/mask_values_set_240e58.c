// SLY3_CFLAGS: -Os -G0
struct AllocationRequest { int bytes, alignment; };
struct MaskBlock {
    int sharers;
    unsigned char values[0x1C];
};
struct MaskOwner {
    unsigned char prefix[0x100];
    struct MaskBlock *block;
};
void *func_001D24D0(struct AllocationRequest *request, void *source);
void *func_001D2538(struct AllocationRequest *request);
void func_00240E58(struct MaskOwner *owner, unsigned int mask, int value)
{
    struct AllocationRequest request;
    unsigned int bit;
    int slot;
    if (!owner->block) {
        request.bytes = 0x20;
        request.alignment = 0x10;
        owner->block = func_001D2538(&request);
        owner->block->sharers = 1;
    } else if (owner->block->sharers >= 2) {
        owner->block->sharers--;
        request.bytes = 0x20;
        request.alignment = 0x10;
        owner->block = func_001D24D0(&request, owner->block);
        owner->block->sharers = 1;
    }
    for (slot = 0, bit = 1; slot < 26; slot++, bit <<= 1) {
        if (bit & mask)
            owner->block->values[slot] = value;
    }
}
