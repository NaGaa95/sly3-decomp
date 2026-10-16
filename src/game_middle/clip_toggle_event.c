// SLY3_CFLAGS: -Os -G0
struct ClipToggleMessage { int key, word4, kind; };
struct ClipToggleOwner {
    unsigned char opaque00[0x10A8];
    int active;
};
struct ClipToggleReceiver {
    unsigned char opaque00[0x10];
    struct ClipToggleOwner *owner;
    unsigned char opaque14[0x34 - 0x14];
    void *clip;
};

int func_00254F80(void *clip);
int func_00238AD8(void *receiver, int event, void *message);

int func_001A37B0(struct ClipToggleReceiver *receiver, int event,
                  struct ClipToggleMessage *message)
{
    if (event == 10 && receiver->clip &&
        func_00254F80(receiver->clip) == message->key) {
        switch (message->kind) {
        case 0x4A:
            receiver->owner->active = 1;
            return 1;
        case 0x4B:
            receiver->owner->active = 0;
            return 1;
        }
    }
    return func_00238AD8(receiver, event, message);
}
