// SLY3_CFLAGS: -Os -G0
struct OutputQueue {
    void *vtable;
    int format, word8, channels, packet_size, address;
    int capacity, write_offset, read_offset, available, pending, total;
};
void func_001DACA8(void *queue, int count, char *buffer);
int func_001DAF98(void *queue, int count, int source_address);
int func_001DADD8(struct OutputQueue *queue, int requested, char *buffer)
{
    int remaining = requested;
    int total = 0;
    int count, read, phase, available;
    if (remaining <= 0 || queue->available < remaining)
        remaining = queue->available;
    if (queue->format == 0x10) {
        remaining &= -(queue->channels << 10);
        func_001DACA8(queue, remaining, buffer);
    } else {
        remaining &= -0x400;
    }
    if (remaining) do {
        available = queue->capacity - queue->write_offset;
        if (remaining < available) count = remaining;
        else count = available;
        if (queue->format == 0x10) {
            count = 0x400;
            phase = queue->total / 1024 / queue->channels % 4;
            if (phase == 0) {
                char *destination = buffer + total;
                destination[1] = 6;
                destination[0x11] = 2;
            } else if (phase == 3) {
                char *destination = buffer + total;
                destination[0x3F1] = phase;
            }
        }
        read = func_001DAF98(queue, count, (int)(buffer + total));
        remaining -= read;
        if (!read) break;
        total += read;
        queue->write_offset += read;
        queue->write_offset %= queue->capacity;
        queue->pending += read;
        queue->available -= read;
        queue->total += read;
        if (requested <= 0) break;
    } while (remaining);
    return total;
}
