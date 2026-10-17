// SLY3_CFLAGS: -Os -G0
struct ValueOwner {
    unsigned char prefix[4];
    int first;
    unsigned char gap0[0x18 - 8];
    int second;
    unsigned char gap1[4];
    int third;
    unsigned char gap2[0xA0 - 0x24];
    void *value;
};
void func_001BE5A8(void *, int);
void func_001BE370(struct ValueOwner *owner, void *value)
{
    if (owner->value != value) {
        int first = owner->first;
        if (first == 1) {
            int second = owner->second;
            if (second == first) {
                if (owner->third == second) {
                    if (value) {
                        owner->value = value;
                        func_001BE5A8((char *)owner + 0x1C, 2);
                    }
                }
            }
        }
    }
}
