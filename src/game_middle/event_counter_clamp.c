// SLY3_CFLAGS: -Os -G0
struct CounterOwner {
    unsigned char opaque000[0x16A4];
    int id16A4;
    unsigned char opaque16A8[0x16E4 - 0x16A8];
    int count16E4;
    int limit16E8;
};
struct EventRecord { int target; int unused4; int code; };
void func_00153738(void *receiver, int kind, void *payload);
void func_001EA3F8(void *receiver, int kind, void *payload)
{
    struct CounterOwner *owner = (struct CounterOwner *)receiver;
    struct EventRecord *event = (struct EventRecord *)payload;
    func_00153738(receiver, kind, payload);
    if (kind == 10 && event->target == owner->id16A4 && event->code == 0x704) {
        int next = owner->count16E4 + 1;
        if (next >= owner->limit16E8)
            next = owner->limit16E8;
        owner->count16E4 = next;
    }
}
