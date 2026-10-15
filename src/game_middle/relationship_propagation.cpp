#include "heap_frame_api.h"
// SLY3_CFLAGS: -Os -G0 -fno-exceptions
// Propagate a relationship state through a child-first collected list.
// Prefix layout and PropagationFields come from verified original Sly3 wrappers.
struct PropagationSubject {
    char prefix[0x44];
    int mode;
    char pad48[0x6C-0x48];
    PropagationSubject *owner;
    char pad70[0x84-0x70];
    int childCount;
    PropagationSubject **children;
    char pad8C[0xF0-0x8C];
    int ownerFirst,ownerSecond,pendingMode,selfFirst,selfSecond;
};
struct PropagationFields {
    PropagationSubject *owner;
    PropagationSubject *self;
    int oldOwnerFirst,oldSelfFirst,oldOwnerSecond,oldSelfSecond;
    PropagationFields(PropagationSubject *p,int first,int second) {
        owner=p->owner;
        self=p;
        if(p) {
            oldSelfFirst=p->selfFirst;
            p->selfFirst=first;
            oldSelfSecond=self->selfSecond;
            self->selfSecond=second;
        }
        if(owner) {
            oldOwnerFirst=owner->ownerFirst;
            owner->ownerFirst=first;
            oldOwnerSecond=owner->ownerSecond;
            owner->ownerSecond=second;
        }
    }
    ~PropagationFields() {
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
struct PropagationRequest {
    int bytes,alignment;
};
class PropagationFrame;
class PropagationFrame {
    public: PropagationFrame() asm("func_001D2770");
    ~PropagationFrame() {
        func_001D2798(this,2);
    }
};
extern "C" {
    extern int D_0036C6E0,D_004794AC;
    extern char D_0036C6E8[],D_00375290[],D_004BC230[];
    void func_00189240(void *,PropagationSubject *,int,int,int);
    PropagationSubject **func_001D2670(PropagationRequest *);
    void func_001899F0(PropagationSubject *,int,int *,PropagationSubject **);
    void func_0018A670(PropagationSubject *,int);
    int func_001880F0(PropagationSubject *);
    void func_00186810(PropagationSubject *,PropagationSubject *);
    void func_001CFE08(void *);
    int func_002845B0(void *,PropagationSubject *,int);
    void func_001871C0(PropagationSubject *);
}
inline PropagationRequest *SetRequest(PropagationRequest *p,int bytes,int alignment) {
    p->bytes=bytes;
    p->alignment=alignment;
    return p;
}
extern "C" void func_00189B08(PropagationSubject *p,int mode) {
    int previous=p->mode;
    if(mode==previous)return;
    if(D_0036C6E0) {
        func_00189240(D_0036C6E8,p,1,mode,p->selfSecond);
        return;
    }
    D_0036C6E0=1;
    {
        PropagationFrame frame;
        PropagationRequest request;
        int count=0;
        PropagationSubject **output=func_001D2670(SetRequest(&request,D_004794AC*4,16));
        func_001899F0(p,mode,&count,output);
        int i;
        for(i=0;i<count;i++) {
            PropagationSubject *child=output[i];
            PropagationFields fields(child,p->selfFirst,p->selfSecond);
            func_0018A670(child,child->pendingMode);
        }
        int j;
        for(j=0;j<count;j++)output[j]->pendingMode=-1;
    }
    D_0036C6E0=0;
    if(func_001880F0(p) && previous!=-1 && previous<2 && p->mode>=2) {
        if(p->owner)func_00186810(p->owner,p);
        if(!p->owner && !p->childCount)func_001CFE08(D_00375290);
    }
    else if(func_001880F0(p) && p->owner) {
        if(p->mode!=2 && func_002845B0(D_004BC230,p,p->mode))func_001871C0(p->owner);
    }
}
