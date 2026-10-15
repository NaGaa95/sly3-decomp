// SLY3_CFLAGS: -Os -G0 -fno-exceptions
// Preserve the original scoped context during each queued lifecycle request.
// This is an observed prefix, not a claimed concrete allocation size.
// The two supplied words are copied unchanged; no identifier or pointer cast is invented.
struct Subject {
    char pad0[0x44];
    int mode;
    char pad48[0x6C-0x48];
    Subject *owner;
    char pad70[0xF0-0x70];
    int ownerFirst,ownerSecond,padF8,selfFirst,selfSecond;
};
struct ScopedFields {
    Subject *owner;
    Subject *self;
    int oldOwnerFirst,oldSelfFirst,oldOwnerSecond,oldSelfSecond;
    ScopedFields(Subject *p,int first,int second) {
        owner=p->owner;
        self=p;
        if(p) {
            oldSelfFirst=p->selfFirst;
            oldSelfSecond=p->selfSecond;
            p->selfFirst=first;
            p->selfSecond=second;
        }
        if(owner) {
            oldOwnerFirst=owner->ownerFirst;
            owner->ownerFirst=first;
            oldOwnerSecond=owner->ownerSecond;
            owner->ownerSecond=second;
        }
    }
    ~ScopedFields() {
        if(owner) {
            owner->ownerFirst=oldOwnerFirst;
            owner->ownerSecond=oldOwnerSecond;
        }
        if(self) {
            self->selfFirst=oldSelfFirst;
            self->selfSecond=oldSelfSecond;
        }
    }
};
#include "relationship_lifecycle_api.h"
extern "C" void func_00189710(Subject *p) {
    ScopedFields fields(p,4,0);
    func_001890B0(p,0,0);
    func_00189640();
}
extern "C" void func_001897C8(Subject *p) {
    ScopedFields fields(p,4,0);
    func_001890B0(p,1,0);
    func_00189640();
}
extern "C" void func_00189880(Subject *p) {
    ScopedFields fields(p,4,0);
    func_001890B0(p,2,0);
    func_00189640();
}
extern "C" void func_00189938(Subject *p) {
    ScopedFields fields(p,4,0);
    func_001890B0(p,3,0);
    func_00189640();
}
