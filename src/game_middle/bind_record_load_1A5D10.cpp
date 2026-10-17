// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "../P2/bis.h"
#include "../P2/heap.h"
struct BindRecord {
    void *first;
    void *second;
};
struct BindMethod { short delta, unused; void (*method)(); };
struct BindOwner {
    unsigned char prefix0[12];
    BindMethod *methods;
    unsigned char gap10[0x128 - 0x10];
    unsigned long flags;
};
extern "C" {
void *func_001D2538(ALLOCREQ *);
void func_001A5EA8(void *record);
void *func_00130218(void *owner, void *target, int mode, void *record);
}
static __inline__ void *ReadBindTarget(BindOwner *owner, CBinaryInputStream *stream)
{
    BindMethod *entry = &owner->methods[55];
    void *adjusted = (char *)owner + entry->delta;
    int index = stream->S16Read();
    return ((void *(*)(void *, int))entry->method)(adjusted, index);
}
extern "C" void func_001A5D10(void *receiver, CBinaryInputStream *stream)
{
    BindOwner *owner = (BindOwner *)receiver;
    int count = stream->U8Read();
    if (count) {
        owner->flags |= 0x10;
        for (int i = 0; i < count; ++i) {
            ALLOCREQ request;
            request.cb = 0xE0;
            request.cbAlign = 0x10;
            unsigned char *record = (unsigned char *)func_001D2538(&request);
            *(void **)(record + 0x04) = ReadBindTarget(owner, stream);
            *(void **)(record + 0x30) = ReadBindTarget(owner, stream);
            *(void **)(record + 0x80) = ReadBindTarget(owner, stream);
            stream->ReadVector((VECTOR *)(record + 0x90));
            *(void **)(record + 0x00) = ReadBindTarget(owner, stream);
            stream->ReadVector((VECTOR *)(record + 0x20));
            func_001A5EA8(record);
            func_00130218(owner, *(void **)(record + 0x04), -1, record);
            func_00130218(owner, *(void **)(record + 0x30), -1, record);
        }
    }
}
