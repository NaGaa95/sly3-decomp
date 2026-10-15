// SLY3_CFLAGS: -Os -G0
struct OutputQueue {
    void *vtable;
    int format, word8, channels, packet_size, address;
    int capacity, write_offset, read_offset, available, pending, total;
};
int func_00291C78(void);
int func_00291C20(void);
void func_001DB098(struct OutputQueue *queue)
{
    if (queue->format == 0x10) {
        int position = func_00291C78() * queue->channels;
        if (position >= 0 && position <= queue->capacity) {
            queue->read_offset = position % queue->capacity;
            if (queue->read_offset == queue->write_offset)
                queue->available = queue->capacity;
            else {
                queue->available = queue->read_offset - queue->write_offset + queue->capacity;
                queue->available %= queue->capacity;
            }
        }
        queue->pending = queue->capacity - queue->available;
    } else {
        queue->available = (func_00291C20() & 0xFFFFFF) - queue->address - queue->write_offset + (queue->capacity - 0x400);
        queue->available %= queue->capacity;
        queue->pending = queue->capacity - queue->available;
        queue->read_offset = queue->write_offset - queue->pending + queue->capacity;
        queue->read_offset %= queue->capacity;
    }
}
int func_001DB1B0(void *queue)
{
    return 0;
}
int func_001DB1B8(void *queue, int count, void *buffer)
{
    int bytes = (unsigned int)count & 0xFFFFFFF0;
    if (bytes > 0x1000) bytes = 0x1000;
    *(volatile unsigned int *)0x1000B420 = (unsigned int)bytes >> 4;
    *(volatile unsigned int *)0x1000B410 = (unsigned int)buffer & 0x0FFFFFFF;
    *(volatile unsigned int *)0x1000B400 = 0x101;
    __asm__ __volatile__("sync" ::: "memory");
    return bytes;
}
int func_001DB218(void *queue)
{
    return 1;
}
