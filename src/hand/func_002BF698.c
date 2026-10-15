// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Count every set bit in the four original input bytes.
int func_002BF698(const unsigned char *bytes)
{
    int count = 0;
    int index;
    for (index = 0; index < 4; index++) {
        unsigned int value = bytes[index];
        while (value) {
            value &= value - 1;
            count++;
        }
    }
    return count;
}
