// Prepare the inactive scratchpad buffer and its DMA tag chain.
// GP varargs alternate source pointer/next byte count, ending with zero/null.
// Only the low64 tag word is written; its original high64 word is preserved.
// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
typedef char *va_list;
#define va_start(ap, last) (ap = ((char *)__builtin_next_arg(last) - (__builtin_args_info(2) >= 8 ? 0 : (8 - __builtin_args_info(2)) * 8)))
#define va_arg(ap, T) (*(T *)((ap += 8) - 8))
#define va_end(ap)
typedef unsigned long DMA_TAG_WORD;
struct BUFFER_ENTRY { int byteCount; char *data; };
struct SCRATCHPAD_BUFFER {
    DMA_TAG_WORD *tags;
    char *data;
    BUFFER_ENTRY entries[8];
    int count;
    int state;
};
struct DMA_CHANNEL {
    volatile unsigned int control;
    int reserved[31];
    volatile unsigned int scratchpadAddress;
};
extern "C" {
extern int D_00349870;
extern SCRATCHPAD_BUFFER D_00475280[2];
extern DMA_CHANNEL *D_0036BD44, *D_0036BD48;
int func_0029FDE8(DMA_CHANNEL *channel, int mode, int unusedTimeout);
void func_0029FD20(DMA_CHANNEL *channel, const void *tags);
}
typedef char dma_tag_word_is_8[sizeof(DMA_TAG_WORD) == 8 ? 1 : -1];
typedef char buffer_entry_is_8[sizeof(BUFFER_ENTRY) == 8 ? 1 : -1];
typedef char dma_channel_prefix_is_132[sizeof(DMA_CHANNEL) == 132 ? 1 : -1];
typedef char scratchpad_buffer_is_80[sizeof(SCRATCHPAD_BUFFER) == 80 ? 1 : -1];

extern "C" void func_0024B578(int byteCount, ...)
{
    SCRATCHPAD_BUFFER *buffer = &D_00475280[1 - D_00349870];
    int count = 0;
    va_list arguments;
    va_start(arguments, byteCount);
    char *destination = buffer->data;
    if (buffer->state == 3)
        func_0029FDE8(D_0036BD44, 0, 0);
    buffer->state = 1;
    char *source = va_arg(arguments, char *);
    if (byteCount) {
        BUFFER_ENTRY *entry = buffer->entries;
        do {
            byteCount = (byteCount + 15) & ~15;
            int nextByteCount = va_arg(arguments, int);
            destination += 16;
            entry->data = destination;
            entry->byteCount = byteCount;
            destination += byteCount;
            char *nextSource = va_arg(arguments, char *);
            if (source) {
                buffer->tags[count * 2] = (DMA_TAG_WORD)(byteCount >> 4)
                    | ((DMA_TAG_WORD)(nextSource ? 3 : 0) << 28)
                    | ((DMA_TAG_WORD)(unsigned int)source << 32);
            }
            source = nextSource;
            byteCount = nextByteCount;
            ++entry;
            ++count;
        } while (byteCount);
    }
    buffer->count = count;
    D_0036BD48->control |= 0x40;
    D_0036BD48->scratchpadAddress = ((unsigned int)buffer->data & 0x0fffffff) | 0x80000000;
    func_0029FD20(D_0036BD48, (const void *)((unsigned int)buffer->tags & 0x0fffffff));
    va_end(arguments);
}
