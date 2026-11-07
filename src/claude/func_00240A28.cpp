// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct P;
struct O {
    int pad0[3];
    virtual void Lock(); virtual void Unlock();
    virtual void Send(int msg, int a, int b, void *pv, int c);
    virtual void Notify(int msg, void *pv);
    virtual void x4(); virtual void x5(); virtual void x6(); virtual void x7(); virtual void x8(); virtual void x9(); virtual void x10(); virtual void x11(); virtual void x12(); virtual void x13(); virtual void x14(); virtual void x15(); virtual void x16(); virtual void x17(); virtual void x18(); virtual void x19(); virtual void x20(); virtual void x21(); virtual void x22(); virtual void x23(); virtual void x24(); virtual void x25(); virtual void x26(); virtual void x27(); virtual void x28(); virtual void x29(); virtual void x30(); virtual void x31(); virtual void x32(); virtual void x33(); virtual void x34(); virtual void x35(); virtual void x36(); virtual void x37(); virtual void x38(); virtual void x39(); virtual void x40(); virtual void x41(); virtual void x42(); virtual void x43(); virtual void x44(); virtual void x45(); virtual void x46(); virtual void x47(); virtual void x48(); virtual void x49(); virtual void x50(); virtual void x51(); virtual void x52(); virtual void x53(); virtual void x54(); virtual void x55(); virtual void x56(); virtual void x57(); virtual void x58(); virtual void x59(); virtual void x60(); virtual void x61(); virtual void x62(); virtual void x63(); virtual void x64(); virtual void x65(); virtual void x66(); virtual void x67(); virtual void x68(); virtual void x69(); virtual void x70(); virtual void x71(); virtual void x72(); virtual void x73(); virtual void x74(); virtual void x75(); virtual void x76();
    virtual int FCheck(P *p);
};
struct P : O { int pad10; O *p14; void *p18; O *p1C; void *p20; char pad24[0x50 - 0x24]; int grf50; };
extern "C" {
extern char D_00475480[];
int func_0025DD38(void *psw, void *a, void *b);
void func_0025DDB0(void *psw, void *a, void *b);
int func_00240E10(void *object, void *key);
void func_00240A28(P *p);
}
struct GUARD {
    P *p;
    GUARD(P *pp) { p = pp; p->Lock(); }
    ~GUARD() { p->Unlock(); }
};
struct THREE { O *p1C; O *p14; P *p; };
struct ARGS2 { void *a; void *b; };
void func_00240A28(P *p)
{
    GUARD guard(p);
    ARGS2 args;
    THREE t;
    P *one;
    if (func_0025DD38(D_00475480, p->p18, p->p1C)) return;
    p->grf50 = func_00240E10(p->p1C, p->p20);
    one = p;
    args.a = &one;
    p->p14->Send(0xC, 0, 1, &args, 0);
    p->p1C->Send(0xC, 0, 1, &args, 0);
    if (!p->p1C->FCheck(p)) return;
    func_0025DDB0(D_00475480, p->p18, p->p1C);
    if (!(p->grf50 & 0x3E)) return;
    t.p1C = p->p1C;
    t.p14 = p->p14;
    t.p = p;
    p->p1C->Notify(0xC, &t);
    p->p14->Notify(0xC, &t);
    args.a = &p->p1C;
    args.b = &p->p20;
    p->p14->Send(0xD, 1, 2, &args, 0);
    args.a = &p->p14;
    p->p1C->Send(0xE, 1, 2, &args, 0);
}
