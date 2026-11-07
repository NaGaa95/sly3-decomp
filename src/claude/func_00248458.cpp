// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct VTE { short d; short p; void (*pfn)(void *); };
struct VT { VTE a[8]; };
struct X { char pad[0xC]; VT *pvt; char pad2[0x60 - 0x10]; X *p60; };
struct Ref;
extern "C" void func_002BF3C8(Ref *, X *);
extern "C" void func_002BF360(Ref *, X *);
struct Ref {
    X *px;
    Ref(X *p) { func_002BF3C8(this, p); }
    Ref(const Ref &r) { func_002BF3C8(this, r.px); }
    Ref &operator=(const Ref &r) { func_002BF360(this, r.px); return *this; }
    ~Ref() { if (px) px->pvt->a[2].pfn((char *)px + px->pvt->a[2].d); }
};
struct S { int c; Ref a[8]; };
struct P { char pad[0x214]; S s; };
extern "C" X *func_00246E68(P *, int);
extern "C" Ref func_00248458(P *p, int n)
{
    X *v = func_00246E68(p, n);
    int i;
    i = 0;
    while (i < p->s.c && p->s.a[i].px->p60 != v) i++;
    if (i == p->s.c) { __asm__("" : : "r"(p)); return Ref(0); } // zero-insn keep-alive: p in s0
    Ref r(p->s.a[i]);
    p->s.c--;
    for (; i < p->s.c; i++) p->s.a[i] = p->s.a[i + 1];
    return r;
}
