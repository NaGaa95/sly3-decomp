// SLY3_CFLAGS: -Os -G0
typedef int Quad __attribute__((mode(TI)));
struct VirtualEntry { short displacement; short pad; void *(*method)(void *); };
struct ChainedObject { unsigned char opaque00[0x24]; struct VirtualEntry *vtable; };
struct VirtualObject { unsigned char opaque00[0xC]; struct VirtualEntry *vtable; };
struct TransformRecord { unsigned char opaque00[0x30]; Quad position; };
void func_001A0740(void *receiver, int unused, Quad *position)
{
    struct ChainedObject *object = (struct ChainedObject *)receiver;
    if (position) {
        struct VirtualEntry *first = object->vtable + 6;
        struct VirtualObject *inner = (struct VirtualObject *)first->method((char *)object + first->displacement);
        struct VirtualEntry *second = inner->vtable + 36;
        struct TransformRecord *record = (struct TransformRecord *)second->method((char *)inner + second->displacement);
        *position = record->position;
    }
}
