// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct EXTRA_KIND_VIEW {
    unsigned char prefix[0x1C];
    int kind;
};
struct EXTRA_CONTEXT_VIEW {
    unsigned char prefix[0x1C];
    struct EXTRA_KIND_VIEW *extra;
};
struct EXTRA_WRAPPER_VIEW {
    unsigned char prefix[0x20];
    struct EXTRA_CONTEXT_VIEW *context;
};

int func_001FDFC0(void *receiver)
{
    return ((struct EXTRA_WRAPPER_VIEW *)receiver)->context->extra->kind;
}
