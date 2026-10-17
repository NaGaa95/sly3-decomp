// SLY3_CFLAGS: -Os -G0
struct Settings {
    unsigned char prefix[0xD8];
    int mode;
    unsigned char gapDC[0xE8 - 0xDC];
    void **slot;
};
void *func_001FE9B8(struct Settings *settings)
{
    switch (settings->mode) {
    case 1:
        return settings->slot;
    case 2:
        return *settings->slot;
    case 3:
        return settings->slot;
    }
    return 0;
}
