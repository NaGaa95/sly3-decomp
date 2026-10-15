// Read the signed minimum count from the original memory queue into the destination.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Only this104-byte reader is recovered; the following registered8-byte method is separate.
struct QueueMemoryInput {
    void *primary;
    const unsigned char *bytes;
    int initialCount;
    int cursor;
    int remainingCount;
};

extern "C" void *memcpy(void *destination, const void *source, unsigned int count);

extern "C" int func_0014F278(QueueMemoryInput *input, int requestedCount, void *destination)
{
    int count = input->remainingCount;
    if (requestedCount < count)
        count = requestedCount;
    memcpy(destination, input->bytes + input->cursor, (unsigned int)count);
    input->cursor += count;
    input->remainingCount -= count;
    return count;
}
