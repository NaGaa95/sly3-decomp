// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Remove original kind4 records owned by the supplied opaque receiver.
#include "owner_parent_link.h"
#include "actor_state_resource_api.h"
#include "actor_resource_lookup_api.h"
struct CleanupList {
    void *head, *tail;
    int link_offset;
};
struct CleanupIterator;
extern CleanupIterator *D_0036AE94;
struct CleanupIterator {
    CleanupList *list;
    void **cursor;
    int link_offset;
    CleanupIterator *previous;
    CleanupIterator(CleanupList *p) : list(p), cursor((void **)p), link_offset(p->link_offset), previous(D_0036AE94) {
        D_0036AE94 = this;
    }
    ~CleanupIterator() {
        D_0036AE94 = previous;
    }
    void *Next() {
        void *node = *cursor;
        cursor = (void **)((unsigned int)node + (unsigned int)link_offset);
        return node;
    }
};
struct CleanupRecord {
    char prefix44[0x44];
    void *owner;
    char unused48[0x54-0x48];
    int kind;
};
struct CleanupGlobalActor {
    char prefix1EC0[0x1EC0];
    void *resource;
};
extern "C" {
    extern CleanupList D_00479C04;
    extern float D_0036BB98, D_0047A3CC;
    void func_001739A8(void *record);
}
extern "C" void func_001B0650(void *receiver) {
    void *object = func_001FBE30(((CleanupGlobalActor *)D_00370AC0)->resource, 0);
    if (object) func_001C7A00(object, 0, 3);
    CleanupIterator iterator(&D_00479C04);
    CleanupRecord *record;
    while ((record = (CleanupRecord *)iterator.Next()) != 0) {
        if (record->kind == 4 && record->owner == receiver) func_001739A8(record);
    }
    D_0047A3CC = D_0036BB98 + 2.0f;
}
