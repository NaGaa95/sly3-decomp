// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Adapted from Sly 2 func_00224380 (contacts: pick the neighbouring actor).
typedef int qword __attribute__((mode(TI)));
struct S;
struct O { int x0; S *p; };
struct SIDE { O *po; int x4; int x8; S *pOther; char pad[0x30]; };
struct EDGE { SIDE as[2]; qword v80; char pad[0xC]; int k9C; char pad2[0xC]; EDGE *pNext; };
struct LN { EDGE *pe; LN *pNext; };
struct Q { char pad[0x60]; int id; LN *pln; };
struct S { char pad[0xDC]; Q *pq; char pad1[0x130 - 0xE0]; int x130; float t134; int x138; char pad2[0x170 - 0x13C]; qword v170; S *x180; O *x184; };
struct CLOCK { float t; };
extern "C" {
extern CLOCK g_clock;
extern int D_00349880[];
void func_0023E068(S *p);
int func_00277640(S *p);
int func_00277510(S *p, S *q);
}
struct SCALAR { qword q; };
static inline qword Scale(const qword &v, const SCALAR &s)
{
    qword r;
    __asm__("vmulx.xyzw %0,%1,%0x" : "=j"(r) : "j"(v), "0"(s.q));
    return r;
}
extern "C" void func_00277388(S *p)
{
    func_0023E068(p);
    if (!p->x130 && g_clock.t - p->t134 < 0.25f)
        return;
    LN *pln = p->pq->pln;
    int id = p->pq->id;
    for (; pln; pln = pln->pNext) {
        EDGE *pe = pln->pe;
        while (pe) {
            int i = pe->as[0].x8 != id;
            if (pe->as[i].po->p != p) {
                pe = pe->pNext;
                continue;
            }
            SIDE *ps = &pe->as[1 - i];
            S *q = ps->pOther;
            if (pe->k9C != 8 && func_00277640(p) && func_00277510(p, q)) {
                SCALAR home;
                p->x180 = q;
                p->x138 = 2;
                p->x184 = ps->po;
                register int bits asm("$3") = D_00349880[i]; // pin: v1 for the coefficient bits
                __asm__("qmtc2.ni %1,%0" : "=j"(home.q) : "r"(bits));
                p->v170 = Scale(pe->v80, home);
            } else if (!p->x130 && p->x138 == -1) {
                p->x138 = 4;
            }
            pe = pe->pNext;
        }
    }
    __asm__("" : : "r"(p));
}
