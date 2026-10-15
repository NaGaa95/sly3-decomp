// Allocate and register an actual 80-byte state instance for an owner and receiver.
// All six GP inputs are explicit; receiver28 and both script0 fields carry real pointers.
// The local guard invokes native receiver-only owner slots on every exit.
// Concrete new-object slots bind239BB0/239BC0/13BB58; names beyond offsets are provisional.
// SLY3_CFLAGS: -Os -G0 -fno-exceptions
// Explicit six GP inputs; concrete slot3 is a six-argument message dispatcher.
struct VTE {
    short d;
    short p;
    void (*pfn)(void *);
};
struct VTE5 {
    short d;
    short p;
    void (*pfn)(void *, int, void *, int, void *, void *);
};
struct VT {
    VTE a[3];
    VTE5 a3;
};
struct P {
    void *script0;
    char pad[0xC - 4];
    VT *pvt;
    char pad2[0x58 - 0x10];
    char dl58[0xC];
};
struct S {
    void *script0;
    int n4;
    int n8;
    VT *pvt;
    char pad[0x24 - 0x10];
    P *p24;
    void *receiver28;
    int n2C;
    int pad30;
    int n34;
    int n38;
    int n3C;
    int pad40;
    float f44;
    int n48;
    int pad4C;
};
struct SW {
    char pad[0x4588];
    char dl[0xC];
    char pool[0x10];
};
extern SW D_00475480;
extern "C" {
    S *func_0011E118(void *);
    S *func_002B5408(S *);
    void *func_00292034(void *, int, int);
    void func_0011AF60(void *, S *);
    void func_002BAA50(S *, void *);
    int func_00239CC0(S *);
    int func_00239AB8(P *, int);
    void func_0023AA48(S *, int, int);
    void func_0023A428(S *, int);
}
struct Lock {
    P *p;
    Lock(P *pp) {
        p = pp;
        p->pvt->a[1].pfn((char *)p + p->pvt->a[1].d);
    }
    ~Lock() {
        p->pvt->a[2].pfn((char *)p + p->pvt->a[2].d);
    }
};
extern "C" void func_00239808(P *p, void *receiver, int state, int mode, int mask, S **pps) {
    S *ps = func_0011E118(D_00475480.pool);
    *pps = ps;
    func_00292034(ps, 0, 0x50);
    func_002B5408(ps);
    ps->receiver28 = receiver;
    ps->n2C = mode;
    ps->n48 = mask;
    ps->p24 = p;
    ps->n38 = -1;
    ps->f44 = 1.0f;
    func_0011AF60(D_00475480.dl, ps);
    func_0011AF60(p->dl58, ps);
    ps->pvt->a[1].pfn((char *)ps + ps->pvt->a[1].d);
    Lock l(p);
    func_002BAA50(ps, p->script0);
    ps->pvt->a3.pfn((char *)ps + ps->pvt->a3.d, 2, 0, 0, 0, 0);
    if (func_00239CC0(ps)) return;
    if (state != -1) {
        int v = func_00239AB8(p, state);
        ps->n34 = v;
        ps->n3C = v;
        func_0023AA48(ps, -1, v);
    }
    func_0023A428(ps, 0);
}
