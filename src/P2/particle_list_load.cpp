// Sly 2 func_0015C1E8 algorithm with the complete original Sly 3 collection fields.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "heap_frame_api.h"
struct FrameToken { int storage[4]; };
struct AllocationRequest { int bytes, alignment; };
struct ChildObject;
struct ChildEntry { short delta, reserved; void (*call)(void *); };
struct ChildObject { char prefix[12]; ChildEntry *table; char reserved10[0x28-0x10]; unsigned long flags; };
struct ChildList { int first, capacity, count; ChildObject **items; };
struct ParticleCollection { char prefix[0xD0]; int count; ChildObject **items; };
extern "C" {
void func_0028FDE0(ParticleCollection *collection, void *stream);
ChildList *func_00151A38(ChildList *list);
void func_002904B0(ParticleCollection *collection, void *stream, ChildList *list);
void *func_001D2538(AllocationRequest *request);
int func_0013B500(void *object, int class_id);
static __inline__ void *AllocateChildList(AllocationRequest *request, int bytes, int alignment)
{
    request->bytes = bytes;
    request->alignment = alignment;
    return func_001D2538(request);
}
void func_00179EA8(ParticleCollection *collection, void *stream)
{
    FrameToken frame;
    ChildList list;
    AllocationRequest request;
    int i;
    func_0028FDE0(collection, stream);
    func_001D2770(&frame);
    func_00151A38(&list);
    func_002904B0(collection, stream, &list);
    collection->items = static_cast<ChildObject **>(AllocateChildList(&request, list.count * 4, 16));
    for (i = 0; i < list.count; ++i) {
        ChildObject *object = list.items[i];
        object->flags |= 1UL << 53;
        if (!func_0013B500(object, 28)) {
            ChildEntry *entry = &object->table[9];
            entry->call((char *)object + entry->delta);
        } else {
            collection->items[collection->count++] = object;
        }
    }
    func_001D2798(&frame, 2);
}
}
