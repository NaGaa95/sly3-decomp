#ifndef SLY3_THREE_ARRAY_OWNER_H
#define SLY3_THREE_ARRAY_OWNER_H
typedef int ArraySetupPacked __attribute__((mode(TI)));
struct ThreeArrayOwner {
    char prefix[0x40];
    int count;
    void *entries;
    char before_other[0x84-0x48];
    void *other;
    int secondary_count;
    void *secondary;
};
void func_00198A20(struct ThreeArrayOwner *owner,ArraySetupPacked value);
#endif
