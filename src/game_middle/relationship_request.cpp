// SLY3_CFLAGS: -Os -G0 -fno-exceptions
// Request the relationship state transition and restore both context views.
// Shared six-member restoration was independently proved for Sly3 func_00189500.
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
    void func_00188868(void *,int);
}
extern "C" void func_00189300(Subject *p, int n, int first, int second) {
    ScopedFields fields(p,first,second);
    if (n == -1) n = 4;
    int nCur = p->mode;
    if (nCur != -1) {
        if(n==3&&p->owner)n=2;
        switch (n) {
            case 4: switch (nCur) {
                case 0: if (func_00189008(p)) {
                    func_00189B08(p, 1);
                    func_00188540(p);
                }
                else {
                    func_00188868(p, 4);
                }
                break;
                case 2: case 3: break;
                default: func_00188540(p);
                break;
            }
            break;
            case 5: func_00188620(p);
            break;
            case 0: case 1: case 2: case 3: {
                int f = (n - nCur == 1);
                switch (nCur) {
                    case 0: if (n == 1) f = func_00189008(p);
                    break;
                    case 1: if (n == 3) f = 1;
                    break;
                    case 3: return;
                }
                if (f) func_00189B08(p, n);
                else func_00188868(p, n);
                break;
            }
        }
    }
}
