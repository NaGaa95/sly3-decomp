// SLY3_CFLAGS: -Os -G0
#include "heap_frame_api.h"
struct TwoArrayRecord { int key; unsigned int unused[2]; };
struct TwoArrayOwner {
    char prefix[0x40];
    int count;
    struct TwoArrayRecord *records;
    char pad48[0x54 - 0x48];
    int reference_count;
    void **references;
};
struct TwoArrayRequest { int bytes, alignment; };
typedef char CheckRecord12[sizeof(struct TwoArrayRecord)==12?1:-1];
typedef char CheckRequest8[sizeof(struct TwoArrayRequest)==8?1:-1];
void *func_001D2670(struct TwoArrayRequest *);
void *func_001D25B0(struct TwoArrayRequest *);
void *func_001D24D0(struct TwoArrayRequest *,void *);
void func_001C7D98(void *,void *);
static inline struct TwoArrayRequest *SetTwoArrayRequest(struct TwoArrayRequest *request,int bytes,int alignment)
{
    request->bytes=bytes;
    request->alignment=alignment;
    return request;
}
void func_0021A928(struct TwoArrayOwner *owner,void *stream)
{
    unsigned char frame[16];
    struct TwoArrayRequest request;
    func_001D2770(frame);
    owner->records=func_001D2670(SetTwoArrayRequest(&request,0xC00,16));
    owner->references=func_001D25B0(SetTwoArrayRequest(&request,0x20,16));
    func_001C7D98(owner,stream);
    {
        void *records=func_001D24D0(SetTwoArrayRequest(&request,owner->count*12,16),owner->records);
        void *references=owner->references;
        owner->records=records;
        owner->references=func_001D24D0(SetTwoArrayRequest(&request,0x20,16),references);
    }
    func_001D2798(frame,2);
}
void func_0021AA00(struct TwoArrayOwner *owner,int key)
{
    if (owner->count < 256) {
        owner->records[owner->count++].key=key;
    }
}
void func_0021AA38(struct TwoArrayOwner *owner,void *reference)
{
    if (owner->reference_count < 8) {
        owner->references[owner->reference_count++]=reference;
    }
}
