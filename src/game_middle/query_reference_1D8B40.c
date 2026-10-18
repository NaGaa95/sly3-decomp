// SLY3_CFLAGS: -Os -G0
typedef int QuerySample __attribute__((mode(TI)));
struct QueryReference {
    unsigned char prefix[0x30];
    int selected;
};
struct QueryChild {
    unsigned char prefix[0x30];
    struct QueryReference *reference;
    int cursor;
    unsigned char gap38[0x90 - 0x38];
    QuerySample sample;
};
void func_001EF5B0(void *reference);
void func_001EF5A0(void *reference);

void func_001D8B40(struct QueryChild *child, struct QueryReference *reference)
{
    if (child->reference)
        func_001EF5B0(child->reference);
    child->reference = reference;
    if (reference) {
        func_001EF5A0(reference);
        child->cursor = 0;
        child->sample = *(QuerySample *)((char *)child->reference + 0x30
                         + 16 * child->reference->selected);
    }
}
