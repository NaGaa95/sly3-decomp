// SLY3_CFLAGS: -Os -G0
#include "heap_frame_api.h"
struct ArraySetupRequest { int bytes, alignment; };
struct ArraySetupOwner {
    char prefix[0xD0];
    int count;
    void *entries;
    unsigned int unusedD8;
    int secondary_count;
    void *secondary_entries;
};
void *func_001D2670(struct ArraySetupRequest *request);
void *func_001D24D0(struct ArraySetupRequest *request,void *old_entries);
void func_0028FDE0(struct ArraySetupOwner *owner,void *input);
void func_00131050(struct ArraySetupOwner *owner,void *input)
{
    unsigned char frame[16];
    struct ArraySetupRequest request;
    struct ArraySetupRequest *allocation;
    func_001D2770(frame);
    allocation = &request;
    request.bytes = 0xC0;
    allocation->alignment = 0x10;
    owner->entries = func_001D2670(allocation);
    request.bytes = 0x80;
    allocation->alignment = 0x10;
    owner->secondary_entries = func_001D2670(allocation);
    func_0028FDE0(owner,input);
    request.bytes = owner->count * 0x18;
    allocation->alignment = 0x10;
    owner->entries = func_001D24D0(allocation,owner->entries);
    request.bytes = owner->secondary_count * 0x10;
    allocation->alignment = 0x10;
    owner->secondary_entries = func_001D24D0(allocation,owner->secondary_entries);
    func_001D2798(frame,2);
}
