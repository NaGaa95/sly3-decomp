// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct SampleSlot {
    unsigned char prefix[0x14];
    float scale;
    unsigned char gap18[0x40 - 0x18];
    qword point;
    unsigned char tail[0x60 - 0x50];
};
struct SampleOwner {
    unsigned char prefix[0x190];
    struct SampleSlot slots[4];
};
void func_0023E290(void *owner);
qword func_001C9428(void *source, void *destination, qword position);
void func_0023E940(void *owner, qword point, float scale);
void func_00206F58(struct SampleOwner *owner)
{
    unsigned int i;
    func_0023E290(owner);
    for (i = 0; i < 4; i++) {
        struct SampleSlot *slot = &owner->slots[i];
        func_0023E940(owner, func_001C9428(owner, 0, slot->point), slot->scale);
    }
}
