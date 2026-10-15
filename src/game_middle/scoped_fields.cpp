// SLY3_CFLAGS: -Os -G0 -fno-exceptions
// Restore subject and owner context words after a requested state transition.
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
extern "C" {
    int func_00189008(void *);
    void func_00189B08(void *,int);
    void func_00188540(void *);
    void func_00188620(void *);
}
extern "C" void func_00189500(Subject *p,int mode,int first,int second) {
    ScopedFields fields(p,first,second);
    if(mode==-1)mode=4;
    if(p->mode!=-1) {
        switch(mode) {
            case 4: if(p->mode==0&&func_00189008(p))func_00189B08(p,1);
            func_00188540(p);
            break;
            case 5:func_00188620(p);
            break;
            case 0:case 1:case 2:case 3:func_00189B08(p,mode);
            break;
        }
    }
}
