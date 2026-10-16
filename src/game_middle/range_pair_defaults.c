// SLY3_CFLAGS: -Os -G0
struct RangeRecord { float high; int count; float limit; };
struct RangeComponent {
    void *owner;
    int slot;
    unsigned char opaque08[0x28];
    struct RangeRecord upper;
    unsigned char opaque3C[4];
    struct RangeRecord lower;
};
static __inline__ void RangeInitialize(struct RangeRecord *record, float limit)
{
    record->high = 45.0f;
    record->limit = limit;
    record->count = 0;
}
void func_001BEE28(void *receiver, void *owner)
{
    struct RangeComponent *component = (struct RangeComponent *)receiver;
    component->owner = owner;
    component->slot = -1;
    RangeInitialize(&component->upper, 40.0f);
    RangeInitialize(&component->lower, -20.0f);
}
