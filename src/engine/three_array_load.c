// SLY3_CFLAGS: -Os -G0
#include "heap_frame_api.h"
#include "three_array_owner.h"
struct ThreeArrayRequest { int bytes,alignment; };
extern ArraySetupPacked D_00317560;
void *func_001D2670(struct ThreeArrayRequest *);
void *func_001D25B0(struct ThreeArrayRequest *);
void *func_001D24D0(struct ThreeArrayRequest *,void *);
void func_001C7D98(struct ThreeArrayOwner *,void *);
static inline struct ThreeArrayRequest *allocation_request(struct ThreeArrayRequest *request,
                                                           int bytes,int alignment)
{
    request->bytes = bytes;
    request->alignment = alignment;
    return request;
}
void func_00198810(struct ThreeArrayOwner *owner,void *input)
{
    unsigned char frame[16];
    struct ThreeArrayRequest request;
    func_001D2770(frame);
    owner->entries = func_001D2670(allocation_request(&request,0x1200,0x10));
    owner->secondary = func_001D25B0(allocation_request(&request,0x100,0x10));
    owner->other = func_001D25B0(allocation_request(&request,0x20,0x10));
    func_00198A20(owner,D_00317560);
    func_001C7D98(owner,input);
    owner->entries = func_001D24D0(allocation_request(&request,owner->count * 0x24,0x10),
                                 owner->entries);
    {
        void *secondary = func_001D24D0(
            allocation_request(&request,owner->secondary_count * 0x10,0x10),owner->secondary);
        void *other = owner->other;
        owner->secondary = secondary;
        owner->other = func_001D24D0(allocation_request(&request,0x20,0x10),other);
    }
    func_001D2798(frame,2);
}
