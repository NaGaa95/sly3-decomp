// SLY3_CFLAGS: -Os -G0
struct Counter {
    unsigned char prefix[0x88];
    int count;
};
void func_00202C20(struct Counter *counter)
{
    counter->count++;
}
