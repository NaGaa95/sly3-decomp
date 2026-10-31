// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; void *pfn; };
struct VT { char pad[0x40]; struct VTE e40; };
struct A { char pad[0xC]; struct VT *vt; char pad2[0x3C - 0x10]; int x3C; };
struct O { char pad[0x29C]; char a29C[1]; };
struct P { char pad[0x10]; struct O *po; char pad2[0x18 - 0x14]; char a18[0x30 - 0x18]; int state; float g34; };
extern struct CLOCK { float t; } g_clock;
void func_00238AE8(void *p);
struct A *func_00238690(void *p, int n);
void func_00238AB8(struct P *p);
static __inline__ void Start(struct A *pa, int k)
{
    pa->x3C = k;
    ((void (*)(void *))pa->vt->e40.pfn)((char *)pa + pa->vt->e40.d);
}
void func_00135A50(struct P *p, int st)
{
    if (st == p->state)
        return;
    func_00238AE8(p->a18);
    p->state = st;
    p->g34 = g_clock.t;
    switch (st) {
    case 0:
        Start(func_00238690(p->po->a29C, 0xC9), 0x1E);
        break;
    case 1:
        Start(func_00238690(p->po->a29C, 0xC9), 0x1F);
        break;
    case 2:
        Start(func_00238690(p->po->a29C, 0xC9), 0x20);
        break;
    case -1:
        func_00238AB8(p);
        break;
    }
}
