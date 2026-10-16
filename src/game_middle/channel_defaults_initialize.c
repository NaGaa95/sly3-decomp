// SLY3_CFLAGS: -Os -G0
struct ChannelView {
    unsigned char opaque000[0xD0];
    int state0D0;
    unsigned char opaque0D4[0x14C - 0xD4];
    int state14C;
    unsigned char opaque150[0x30C - 0x150];
    int enabled30C;
    unsigned char opaque310[0x338 - 0x310];
    int enabled338;
};
void func_00165938(void *channel);
void func_00167AB0(void *owner, int first, int second, int selection, int flags);
void func_001679E0(void *owner, float value);
void func_00167A50(void *owner, float value);
void func_001E8438(void *receiver)
{
    struct ChannelView *channel = (struct ChannelView *)receiver;
    func_00165938(receiver);
    channel->state14C = -1;
    func_00167AB0(receiver, 0, 0, 0x80, 0x80);
    func_001679E0(receiver, 4.0f);
    func_00167A50(receiver, 1000.0f);
    channel->state0D0 = -1;
    channel->enabled30C = 1;
    channel->enabled338 = 1;
}
