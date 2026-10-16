// SLY3_CFLAGS: -Os -G0
typedef int Quad __attribute__((mode(TI)));
struct VirtualEntry { short displacement; short pad; void *(*method)(void *); };
struct VirtualObject { unsigned char opaque00[0xC]; struct VirtualEntry *vtable; };
struct TransformRecord { unsigned char opaque00[0x30]; Quad position; };
float func_002A3EE8(float y, float x);
void func_001A29B8(void *receiver, int unused, Quad *position, float *heading)
{
    struct VirtualObject *object = (struct VirtualObject *)receiver;
    if (position) {
        struct VirtualEntry *entry = object->vtable + 36;
        struct TransformRecord *record = (struct TransformRecord *)entry->method((char *)object + entry->displacement);
        *position = record->position;
    }
    if (heading) {
        struct VirtualEntry *entry = object->vtable + 36;
        float *axis = (float *)entry->method((char *)object + entry->displacement);
        *heading = func_002A3EE8(axis[1], axis[0]);
    }
}
