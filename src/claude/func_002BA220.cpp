// Reference: Sly 2 src/hand/func_002566D8.cpp; target Sly 3 0x002BA220.
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -fno-exceptions
struct VT { short d; short pad; void *pfn; };
struct O { char pad[0xC]; VT *vt; char x10[4]; };
struct DESC { int cb; int align; DESC(int c, int a) { cb = c; align = a; } };
struct MARK { int a[4]; };
extern "C" {
void *func_001D2770(MARK *);
void func_001D2798(MARK *, int);
void *func_001D25B0(DESC *);
int func_001191E0(void *);
void Reserve(void *, int) asm("Reserve__9CDynArrayi");
void *memset(void *, int, int);
}

extern "C" void func_002BA220(O *p, void *pv)
{
    ((void (*)(void *))p->vt[2].pfn)((char *)p + p->vt[2].d);
    MARK m;
    func_001D2770(&m);
    DESC d(4, 0x10);
    void *buf = func_001D25B0(&d);
    register int n asm("s0") = func_001191E0(pv); /* pin: s0/s1 allocation tie with p */
    Reserve(p->x10, n);
    if (n > 0) do {
        memset(buf, 0, 4);
        ((void (*)(void *, void *, void *))p->vt[4].pfn)((char *)p + p->vt[4].d, buf, pv);
        ((void (*)(void *, void *))p->vt[5].pfn)((char *)p + p->vt[5].d, buf);
    } while (--n);
    func_001D2798(&m, 2);
}
