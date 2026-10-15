// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct MSG { int cb; int nKind; };
struct COLOR_SHARED48 {
    unsigned char prefix[0x2C];
    short references;
    short changed;
};
struct COLOR_OWNER_PREFIX {
    unsigned char prefix[0xD8];
    int kind;
};
struct COLOR_CONTEXT {
    struct COLOR_OWNER_PREFIX *owner;
    unsigned char reserved04[0x18];
    struct COLOR_SHARED48 *extra;
};
struct COLOR_WRAPPER {
    unsigned char prefix[0x20];
    struct COLOR_CONTEXT *context;
};
void *func_001D24D0(struct MSG *, void *);

static inline struct MSG *ColorRequest(struct MSG *request, int bytes, int alignment)
{
    request->cb = bytes;
    request->nKind = alignment;
    return request;
}

void *func_001FDC18(void *receiver, int mode)
{
    struct COLOR_CONTEXT *context = ((struct COLOR_WRAPPER *)receiver)->context;
    if (mode == 1) {
        if (context->owner->kind != 2) {
            struct COLOR_SHARED48 *extra = context->extra;
            if (extra->references >= 2) {
                struct MSG request;
                struct COLOR_SHARED48 *source;
                --extra->references;
                source = context->extra;
                context->extra = func_001D24D0(
                    ColorRequest(&request, sizeof(struct COLOR_SHARED48), 16), source);
                context->extra->references = mode;
            }
        }
        context->extra->changed = 1;
    }
    return context->extra;
}
