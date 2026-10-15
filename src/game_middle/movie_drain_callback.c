// SLY3_CFLAGS: -Os -G0
struct DecoderByteQueue {
    char *buffer;
    int capacity, free_offset, allocated_offset;
    int free, allocated, drained, total;
};
struct DecoderDrain {
    unsigned char opaque[0x160];
    struct DecoderByteQueue queue;
    unsigned char stream[0];
};
int func_001DC430(void *decoder, int wait);
void func_001DB490(void *stream);
void *func_00292034(void *buffer, int value, int bytes);
int func_0014F1C8(void *queue, int count, const void *source);
void *func_002BE7F8(void *output);
void func_0014F240(void *queue, int count);
int func_0014F0A0(void *queue, int count, void *output);
int func_001DB5C8(void *decoder_object, void *event,
    struct DecoderDrain *decoder)
{
    char scratch[64] __attribute__((aligned(16)));
    while (decoder->queue.allocated < 0x1000) {
        int status = func_001DC430(decoder, 1);
        if (status == 2) {
            func_00292034(scratch, 0, 64);
            func_0014F1C8(&decoder->queue, 64 - decoder->queue.allocated % 32, scratch);
            break;
        }
        if (status == 1) func_001DB490(decoder->stream);
    }
    func_002BE7F8(scratch);
    func_0014F240(&decoder->queue, 0);
    func_0014F0A0(&decoder->queue, 0, scratch);
    return 1;
}
