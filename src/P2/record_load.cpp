// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "heap.h"
#include "heap_frame_api.h"

struct MSG { int cb; int nKind; };
union LOAD_REQUEST { ALLOCREQ slot; MSG copy; };
struct ENTRY28 { unsigned char storage[28]; };
struct LOADED_RECORD
{
    unsigned char prefix[0xA];
    short count;
    ENTRY28 *entries;
};
struct LOAD_OWNER
{
    unsigned char prefix[0x20];
    LOADED_RECORD *record;
};
extern "C" {
void *func_001D2670(ALLOCREQ *);
void *func_001D24D0(MSG *, void *);
void func_001519C8(void *, void *);
void func_001FCF10(void *, void *);
}

inline ALLOCREQ *SlotRequest(ALLOCREQ *request, int bytes, int alignment)
{
    request->cb = bytes;
    request->cbAlign = alignment;
    return request;
}
inline MSG *CopyRequest(MSG *request, int bytes, int alignment)
{
    request->cb = bytes;
    request->nKind = alignment;
    return request;
}

extern "C" void func_001FD198(void *receiver, void *stream)
{
    LOAD_OWNER *object = (LOAD_OWNER *)receiver;
    char frame[16];
    func_001D2770(frame);
    LOAD_REQUEST request;
    object->record->entries = (ENTRY28 *)func_001D2670(
        SlotRequest(&request.slot, 0x380, 16));
    func_001519C8(receiver, stream);
    func_001FCF10(object->record, stream);
    LOADED_RECORD *record = object->record;
    int bytes = record->count * (int)sizeof(ENTRY28);
    ENTRY28 *entries = record->entries;
    object->record->entries = (ENTRY28 *)func_001D24D0(
        CopyRequest(&request.copy, bytes, 16), entries);
    func_001D2798(frame, 2);
}
