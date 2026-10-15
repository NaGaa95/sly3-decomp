// Sly 2 reference: src/hand/func_001F09D8.cpp.
// GNU declaration labels establish canonical Sly 3 symbols without executable assembly.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct VTE { short d; short p; void (*pfn)(void *); };
struct VT { VTE a[3]; };
struct P { char pad[0xC]; VT *pvt; char pad2[0x24 - 0x10]; void *p24; char pad3[0x30 - 0x28]; void *p30; int n34; int n38; int n3C; };
extern "C" int func_00239CC0(P *) __asm__("func_00239CC0");
extern "C" int func_00239AB8(void *, int) __asm__("func_00239AB8");
extern "C" void func_00137B00(void *) __asm__("func_00137B00");
extern "C" void func_0023AA48(P *, int, int) __asm__("func_0023AA48");
extern "C" void func_0023A428(P *, int) __asm__("func_0023A428");
struct Lock {
    P *p;
    Lock(P *pp) { p = pp; p->pvt->a[1].pfn((char *)p + p->pvt->a[1].d); }
    ~Lock() { p->pvt->a[2].pfn((char *)p + p->pvt->a[2].d); }
};
extern "C" void func_0023A070(P *p, int n) __asm__("func_0023A070");
extern "C" void func_0023A070(P *p, int n)
{
    if (!func_00239CC0(p)) {
        Lock l(p);
        int m = func_00239AB8(p->p24, n);
        if (p->n34 == m && (p->n3C == m || p->n3C == -1)) return;
        {
            void *pv = p->p30;
            int old;
            if (pv) {
                p->p30 = 0;
                func_00137B00(pv);
            }
            old = p->n34;
            p->n38 = -1; p->n3C = m; p->n34 = m;
            func_0023AA48(p, old, m);
            func_0023A428(p, 0);
        }
    }
}
