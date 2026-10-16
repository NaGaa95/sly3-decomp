// SLY3_CFLAGS: -Os -G0
#include "heap_frame_api.h"

struct LoadArray32Record { unsigned char storage[32]; };
struct LoadArray32View {
    unsigned char beforeCount[0x174];
    unsigned int count;
    struct LoadArray32Record *records;
};
struct LoadArray32Request { unsigned int bytes; int alignment; };

void *func_001D2670(struct LoadArray32Request *);
void *func_001D24D0(struct LoadArray32Request *, void *);
void func_0023C0B8(void *, void *);

static inline void SetLoadArrayRequest(struct LoadArray32Request *request,
    unsigned int bytes, int alignment)
{
    request->bytes = bytes;
    request->alignment = alignment;
}

void func_00281888(struct LoadArray32View *owner, void *stream)
{
    unsigned char frame[16];
    struct LoadArray32Request request;
    func_001D2770(frame);
    SetLoadArrayRequest(&request, 0x2000, 16);
    owner->records = func_001D2670(&request);
    func_0023C0B8(owner, stream);
    SetLoadArrayRequest(&request, owner->count * sizeof(struct LoadArray32Record), 16);
    owner->records = func_001D24D0(&request, owner->records);
    func_001D2798(frame, 2);
}
