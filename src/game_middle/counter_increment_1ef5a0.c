// SLY3_CFLAGS: -Os -G0
struct CounterOwner {
    unsigned char prefix[0x288];
    int count;
};
void func_001EF5A0(struct CounterOwner *owner)
{
    owner->count++;
}
