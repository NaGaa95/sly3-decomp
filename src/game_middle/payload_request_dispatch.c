// SLY3_CFLAGS: -Os -G0
struct Method { short adjustment, word2; void *function; };
struct RequestOwner {
    unsigned char prefix[0xC];
    struct Method *methods;
    unsigned char gap10[0x500 - 0x10];
    void *contextOwner;
    float contextChanged;
    int contextKind;
    unsigned char gap50C[0xA00 - 0x50C];
    int requested;
};
void func_001B40F0(void *context, int kind, void *payload, void *record);
void func_001AFAA8(struct RequestOwner *owner, void *payload)
{
    if (payload) {
        owner->requested = 1;
        func_001B40F0((char *)owner + 0x500, 6, payload, 0);
    } else if (owner->contextKind == 6) {
        struct Method *method = &owner->methods[99];
        ((void (*)(void *, int))method->function)((char *)owner + method->adjustment, 0);
    }
}
