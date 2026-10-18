// SLY3_CFLAGS: -Os -G0
struct AllocationRequest { int bytes, alignment; };
struct EnabledOwner {
    unsigned char prefix[0x4C8];
    int enabled;
    void *child;
};
void *func_001D2538(struct AllocationRequest *request);
void func_001C0370(void *child, void *owner);
void func_001C12B0(void *child);
void func_00251A58(struct EnabledOwner *owner, int enabled)
{
    struct AllocationRequest request;
    if (owner->enabled == enabled)
        return;
    owner->enabled = enabled;
    if (enabled) {
        if (!owner->child) {
            request.bytes = 0x420;
            request.alignment = 0x10;
            owner->child = func_001D2538(&request);
            func_001C0370(owner->child, owner);
        }
    } else {
        func_001C12B0(owner->child);
    }
}
