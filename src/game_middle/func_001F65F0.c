// Actor defaults: base initialisation, mask values, then four default words; the tagged word at +0x3C gets bit 1
// set either through its pointer (low bit clear) or in place (low bit set).
// SLY3_CFLAGS: -Os -G0
struct TagDefaults {
    unsigned char prefix0[0x3C];
    int tagged_flags;
    unsigned char gap40[0x130 - 0x40];
    int word130;
    unsigned char gap134[0x164 - 0x134];
    int word164;
    unsigned char gap168[0x170 - 0x168];
    int word170;
    unsigned char gap174[0x19C - 0x174];
    int word19C;
};
static inline int FIsPtr(int f) { return !(f & 1); }
void func_0023AE08(void *receiver);
void func_00240E58(void *receiver, unsigned int mask, int value);
void func_001F65F0(struct TagDefaults *receiver)
{
    int f;
    func_0023AE08(receiver);
    func_00240E58(receiver, 0x0200017E, 2);
    f = receiver->tagged_flags;
    receiver->word130 = -1;
    receiver->word164 = 1;
    receiver->word170 = 1;
    receiver->word19C = -1;
    if (FIsPtr(f))
        *(int *)f |= 2;
    else
        receiver->tagged_flags = f | 2;
}
