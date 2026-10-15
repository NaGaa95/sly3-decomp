// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0

typedef struct RuntimeRpcPacketStatusView {
    unsigned char opaque00[16];
    unsigned int flags;
    unsigned char opaque14[4];
    int request_serial;
} RuntimeRpcPacketStatusView;

typedef struct RuntimeRpcStatusHeadView {
    RuntimeRpcPacketStatusView *packet;
    int request_serial;
} RuntimeRpcStatusHeadView;

typedef char RuntimeRpcPacketFlagsOffset16[
    ((unsigned int)&((RuntimeRpcPacketStatusView *)0)->flags) == 16 ? 1 : -1];
typedef char RuntimeRpcPacketSerialOffset24[
    ((unsigned int)&((RuntimeRpcPacketStatusView *)0)->request_serial) == 24 ? 1 : -1];

int func_00296108(void *storage)
{
    RuntimeRpcStatusHeadView *rpc = (RuntimeRpcStatusHeadView *)storage;
    RuntimeRpcPacketStatusView *packet = rpc->packet;

    if (packet == 0 || rpc->request_serial != packet->request_serial ||
        !(packet->flags & 1)) {
        return 0;
    }
    return 1;
}
