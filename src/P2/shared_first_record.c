// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef struct Record Record;
typedef struct { unsigned char prefix[0x50]; short references, changed; unsigned char tail[12]; } SHARED96;
typedef struct { unsigned char prefix[0x80]; short references, changed; unsigned char tail[12]; } SHARED144;
typedef struct { unsigned char prefix[0xD8]; int kind; } RECORD_TYPE;
typedef struct { RECORD_TYPE *type; unsigned char reserved04[12]; SHARED96 *first; SHARED144 *second; } SHARED_CONTEXT;
typedef struct { unsigned char prefix[0x20]; SHARED_CONTEXT *context; } RECORD_OWNER;
struct MSG { int cb; int nKind; };
void *func_001D24D0(struct MSG *, void *);
static inline struct MSG *SharedRequest(struct MSG *request, int bytes, int alignment)
{
    request->cb = bytes;
    request->nKind = alignment;
    return request;
}

Record * func_001FD540(void *receiver, int mode)
{
    RECORD_OWNER *object = receiver;
    if (mode == 1)
    {
        if (object->context->type->kind != 2)
        {
            SHARED96 *record = object->context->first;
            if (record->references >= 2)
            {
                struct MSG request;
                SHARED96 *source;
                --record->references;
                source = object->context->first;
                object->context->first = func_001D24D0(
                    SharedRequest(&request, sizeof(SHARED96), 16), source);
                object->context->first->references = mode;
            }
        }
        object->context->first->changed = 1;
    }
    return (Record *) object->context->first;
}
