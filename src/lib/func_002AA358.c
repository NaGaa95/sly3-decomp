// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
typedef struct { char pad[0x868]; void *mp; } DEC;
typedef struct RuntimeMpegWorkArea {
    unsigned int size;
    unsigned int base;
    unsigned int cursor;
} RuntimeMpegWorkArea;
void _sceMpegError(DEC *decoder, const char *message);
extern const char D_0032C5D8[];

void *func_002AA358(DEC *decoder, RuntimeMpegWorkArea *area,
                    unsigned int bytes, unsigned int alignment)
{
    unsigned int rounded = (area->cursor + alignment - 1) / alignment * alignment;
    unsigned int end = rounded + bytes;
    if (area->size + area->base < end) {
        _sceMpegError(decoder, D_0032C5D8);
        return 0;
    }
    area->cursor = end;
    return (void *)rounded;
}
