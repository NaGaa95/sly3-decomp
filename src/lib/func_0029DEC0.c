// Reference: Sly 2 src/lib/decode_uleb128.c; target Sly 3 0x0029DEC0.
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
/* libgcc frame.c */
unsigned char *decode_uleb128(unsigned char *buf, unsigned int *r)
{
    unsigned int shift = 0, byte, result;
    byte = *buf++;
    result = byte & 0x7f;
    while (byte & 0x80) {
        byte = *buf++;
        shift += 7;
        result |= (byte & 0x7f) << shift;
    }
    *r = result;
    return buf;
}
