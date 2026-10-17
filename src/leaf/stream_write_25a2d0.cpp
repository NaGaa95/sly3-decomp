// SLY3_CFLAGS: -Os -G0 -fno-exceptions
struct OutputWriteAccess {
    char *memory;
    int capacity, memoryCount, fd, total, bufferCapacity, bufferCount;
    char *buffer;
};
extern "C" {
void func_001D2898(void *destination, const void *source, unsigned int bytes);
void func_0025A400(OutputWriteAccess *stream);
int func_0025A2D0(OutputWriteAccess *stream, const char *data, int bytes)
{
    int written = 0;
    char *memory = stream->memory;
    if (memory && stream->capacity) {
        if (bytes == 0)
            return 0;
        int room = stream->capacity - stream->memoryCount;
        if (room < bytes)
            bytes = room;
    }
    if (bytes == 0)
        return 0;
    if (memory) {
        written = bytes;
        func_001D2898(memory + stream->memoryCount, data, bytes);
        stream->memoryCount += bytes;
    } else {
        while (written < bytes) {
            int remaining = bytes - written;
            int room = stream->bufferCapacity - stream->bufferCount;
            int count = room < remaining ? room : remaining;
            if (count) {
                func_001D2898(stream->buffer + stream->bufferCount, data + written, count);
                written += count;
                stream->bufferCount += count;
            }
            if (stream->bufferCount == stream->bufferCapacity)
                func_0025A400(stream);
        }
    }
    stream->total += written;
    return bytes;
}
}
