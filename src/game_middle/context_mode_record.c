// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct ContextModeRecord {
    unsigned char bytes[96];
} __attribute__((aligned(16)));

struct ContextModeState {
    char prefix[4];
    int state;
    char gap8[0x18 - 8];
    int mode;
    char gap1C[0x40 - 0x1C];
    struct ContextModeRecord record;
};

void func_001BDBB0(void *, int);
void *func_00292034(void *, int, unsigned int);

void func_001BDA88(void *receiver, int mode, const void *record)
{
    struct ContextModeState *context = (struct ContextModeState *)receiver;
    if (context->state != -1) {
        if (context->mode == 1 || mode != 1)
            return;
        func_001BDBB0(receiver, 2);
        func_001BDBB0(receiver, -1);
    }
    context->mode = mode;
    if (record)
        context->record = *(const struct ContextModeRecord *)record;
    else
        func_00292034(&context->record, 0, sizeof(context->record));
    func_001BDBB0(receiver, 0);
}
