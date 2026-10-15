// Sly 2 reference: src/hand/func_001F0FD8.cpp.
// GNU declaration labels establish canonical Sly 3 symbols without executable assembly.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct VTE { short d; short p; void *pfn; };
struct VT { VTE a[6]; };
struct Q { char pad[0xC]; VT *pvt; };
struct P { char pad[0xC]; VT *pvt; char pad2[0x28 - 0x10]; Q *pq; };
extern "C" void func_0013BE38(P *, int, int) __asm__("func_0013BE38");
struct Lock {
    P *p;
    Lock(P *pp) { p = pp; ((void (*)(void *))p->pvt->a[1].pfn)((char *)p + p->pvt->a[1].d); }
    ~Lock() { ((void (*)(void *))p->pvt->a[2].pfn)((char *)p + p->pvt->a[2].d); }
};
extern "C" void func_0023A678(P *p, int a, int b) __asm__("func_0023A678");
extern "C" void func_0023A678(P *p, int a, int b)
{
    Lock l(p);
    Q *q = p->pq;
    if (q) ((void (*)(void *, int, int))q->pvt->a[5].pfn)((char *)q + q->pvt->a[5].d, a, b);
    func_0013BE38(p, a, b);
}
