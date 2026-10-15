// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int QueuePosition __attribute__((mode(TI)));
struct P;
struct QueueEntry { int key, reserved, parameter, count; };
struct QueueAdvanceView {
    char prefix[0x414];
    QueueEntry entries[8];
    int total, index;
    char reserved49C[8];
    int override_count, veto;
    void *owner;
};
extern "C" {
extern char D_0036C700[];
int func_001F1F78(void *);
void func_001854C8(void *, int, void *);
void *func_001F2C00(void *, int, QueuePosition, int);
void func_001F17C8(P *, int);
void func_001F1CF8(P *);
}

extern "C" void *func_001F1E18(P *receiver, QueuePosition position, int mode)
{
    QueueAdvanceView *source = (QueueAdvanceView *)receiver;
    if (!func_001F1F78(receiver))
        return 0;
    if (!source->override_count) {
        source->veto = 0;
        func_001854C8(D_0036C700, 17, receiver);
    }
    if (source->veto)
        return 0;

    QueueEntry *entry = &source->entries[source->index];
    int count = 1;
    if (!source->override_count)
        count = entry->count;
    void *result = func_001F2C00(source->owner, count, position, mode);
    func_001F17C8(receiver, -1);
    if (source->override_count)
        source->override_count = 0;
    else
        ++source->index;
    func_001F1CF8(receiver);
    return result;
}
