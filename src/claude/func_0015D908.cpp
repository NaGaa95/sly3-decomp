// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
union M4 { struct { qword r[4]; } q; float af[4][4]; };
union QF { float af[4]; qword q; };
struct LO;
struct VTE { short d; short pad; void *pfn; };
struct LOV { char pad[0x20]; VTE ae[64]; };
struct LO { int a[3]; LOV *pvt; };
static inline VTE *Pvte(LO *plo, int off) { return (VTE *)((char *)plo->pvt + off); }
static inline M4 *VMat(LO *plo) { VTE *e = Pvte(plo, 0x120); return ((M4 *(*)(LO *))e->pfn)((LO *)((char *)plo + e->d)); }
struct DD { char pad[0x80]; qword v80; };
struct PO : LO { char pad[0xD8 - 0x10]; DD *pD8; char pad1[0x260 - 0xDC]; qword v260; char pad2[0x1520 - 0x270]; int x1520; };
struct PL : LO { char pad[0x1AD4 - 0x10]; int x1AD4; };
struct MSG { qword pos; float g0; float g1; };
struct X : LO {
    char pad[0x144 - 0x10]; PO *p144; char pad1[0x258 - 0x148]; LO *p258; void *p25C; char x260[4]; float g264; float g268;
};
static const QF s_posDefault = { { 0.0f, 0.0f, 300.0f, 0.0f } };
extern "C" {
extern PL *D_0038AE90;
void func_0015C958(X *p);
qword func_001C9428(X *p, int n, qword q);
int func_0013B500(PO *p, int n);
int func_00156700(PO *p);
qword func_00212480(qword a, qword b, qword c, float g);
void func_001E2E88(PL *p, int n);
void func_00153F68(PO *p, qword pos, float g0, float g1);
void func_00137588(void *p, X *px, float g0, int n, float g1, void *pv);
void func_0015D908(X *p);
}
static inline qword Sub(const qword &a, const qword &b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline float GY(qword q) { float g; __asm__("pextuw %0, $0, %1" : "=r"(g) : "r"(q)); return g; }
static inline bool FLt(float a, float b) { return a < b; }
void func_0015D908(X *p)
{
    func_0015C958(p);
    qword pos;
    if (p->p258)
        pos = VMat(p->p258)->q.r[3];
    else
        pos = func_001C9428(p, 0, s_posDefault.q);
    if (func_0013B500(p->p144, 0x33)) {
        PO *ps = p->p144;
        if (!func_00156700(ps)) {
            if (ps == (PO *)D_0038AE90 && ps->x1520 == 0x16) {
                qword r = func_00212480(VMat(p)->q.r[3], Sub(pos, ps->v260), ps->pD8->v80, p->g264);
                float g = GY(r);
                VTE *e = Pvte(D_0038AE90, 0x130);
                qword q = ((qword (*)(LO *))e->pfn)((LO *)((char *)D_0038AE90 + e->d));
                if (FLt(GY(q), g)) {
                    VTE *e2 = Pvte(ps, 0x140);
                    ((void (*)(LO *, qword))e2->pfn)((LO *)((char *)ps + e2->d), r);
                    if (D_0038AE90->x1AD4 == 1)
                        func_001E2E88(D_0038AE90, 0);
                }
            } else {
                func_00153F68(ps, pos, p->g264, p->g268);
            }
        }
    } else if (func_0013B500(p->p144, 0x3A)) {
        MSG msg;
        msg.pos = pos;
        msg.g0 = p->g264;
        msg.g1 = p->g268;
        VTE *e = Pvte(p->p144, 0x20);
        ((void (*)(LO *, int, MSG *))e->pfn)((LO *)((char *)p->p144 + e->d), 8, &msg);
    }
    func_00137588(p->p25C, p, 0.0f, 0, 1.0f, p->x260);
}
