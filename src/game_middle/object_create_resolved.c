// SLY3_CFLAGS: -Os -G0
typedef int Quad __attribute__((mode(TI)));
struct CreatedObject { unsigned char opaque00[0x20]; void *handle20; unsigned char opaque24[0xC]; unsigned char embedded30[0x10]; };
void *func_001C9A50(unsigned int requested_bytes);
void *func_002BE830(void *object);
void *func_001ED460(void *owner, Quad value, void *embedded);
void *func_001ED190(void *owner, Quad value, void *embedded, int flag);
void *func_001ED290(void *owner, Quad value, int variant)
{
    struct CreatedObject *object = (struct CreatedObject *)func_002BE830(func_001C9A50(0x40));
    if (variant)
        object->handle20 = func_001ED460(owner, value, object->embedded30);
    else
        object->handle20 = func_001ED190(owner, value, object->embedded30, 1);
    return object;
}
