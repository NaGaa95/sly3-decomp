// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct COLOR_RGBA {
    unsigned char r, g, b, a;
    COLOR_RGBA(unsigned char red, unsigned char green,
               unsigned char blue, unsigned char alpha)
        : r(red), g(green), b(blue), a(alpha) {}
};
struct COLOR_BUFFER {
    unsigned char reserved00[0x214];
    int paired;
    int count;
    COLOR_RGBA colors[32];
};
struct COLOR_EXTRA_VIEW {
    unsigned char reserved00[0x20];
    COLOR_BUFFER *buffer;
};
extern "C" void *func_001FDC18(void *, int);

extern "C" void func_001FDD40(void *receiver,
    int red0, int green0, int blue0, int alpha0,
    int red1, int green1, int blue1, int alpha1)
{
    COLOR_EXTRA_VIEW *extra = (COLOR_EXTRA_VIEW *)func_001FDC18(receiver, 1);
    COLOR_BUFFER *buffer = extra->buffer;
    if (buffer->count == 0)
        buffer->paired = red1 >= 0;
    else if (buffer->count + (buffer->paired ? 2 : 1) > 32)
        return;

    buffer->colors[buffer->count++] = COLOR_RGBA(red0, green0, blue0, alpha0);
    if (buffer->paired)
        buffer->colors[buffer->count++] = COLOR_RGBA(red1, green1, blue1, alpha1);
}
