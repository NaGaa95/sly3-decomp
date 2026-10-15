// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct MSG { int cb; int nKind; };
struct EXTRA36
{
    unsigned char prefix[0x20];
    short references;
    short changed;
};
struct RECORD_TYPE
{
    unsigned char prefix[0xD8];
    int kind;
};
struct EXTRA_CONTEXT
{
    struct RECORD_TYPE *type;
    unsigned char reserved04[0x18];
    struct EXTRA36 *extra;
};
struct EXTRA_OWNER
{
    unsigned char prefix[0x20];
    struct EXTRA_CONTEXT *context;
};
void *func_001D24D0(struct MSG *, void *);

static inline struct MSG *ExtraRequest(struct MSG *request, int bytes, int alignment)
{
    request->cb = bytes;
    request->nKind = alignment;
    return request;
}

void *func_001FE0C0(void *receiver, int mode)
{
    struct EXTRA_CONTEXT *context = ((struct EXTRA_OWNER *)receiver)->context;
    if (mode == 1)
    {
        if (context->type->kind != 2)
        {
            struct EXTRA36 *extra = context->extra;
            if (extra->references >= 2)
            {
                struct MSG request;
                struct EXTRA36 *source;
                --extra->references;
                source = context->extra;
                context->extra = func_001D24D0(
                    ExtraRequest(&request, sizeof(struct EXTRA36), 16), source);
                context->extra->references = mode;
            }
        }
        context->extra->changed = 1;
    }
    return context->extra;
}
