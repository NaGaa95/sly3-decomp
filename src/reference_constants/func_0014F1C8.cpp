// Fill the actual bytequeue using a20-byte stack memory-input protocol.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Stack memory input used by the byte queue's real CbFill callback.
struct QueueMemoryInput {
    void *primary;
    const unsigned char *bytes;
    int initialCount;
    int cursor;
    int remainingCount;
};

extern "C" const unsigned int D_00353C48[6];
extern "C" void *func_002BC4B8(void *input);
extern "C" int func_0014EF98(void *queue, int count, void *input);

extern "C" int func_0014F1C8(void *queue, int count, unsigned char *bytes)
{
    int copiedCount;
    if (!count) {
        copiedCount = 0;
    } else {
        QueueMemoryInput input;
        func_002BC4B8(&input);
        input.bytes = bytes;
        input.primary = (void *)D_00353C48;
        input.remainingCount = count;
        input.initialCount = count;
        input.cursor = 0;
        copiedCount = func_0014EF98(queue, count, &input);
    }
    return copiedCount;
}


