// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
struct M4 { qword r[4]; };
struct VEntry { short delta; short pad; struct M4 *(*get)(void *); };
struct LO { char pad[0xC]; struct VEntry *table; };
struct PO { struct LO lo; char pad10[0x1144 - 0x10]; int grf1144; };
struct ALO { struct LO lo; char pad10[0x250 - 0x10]; int k250; };
struct ST { char pad[0x10]; struct PO *ppo; char pad14[0x38 - 0x14]; struct ALO *palo; };
void func_00119EA8(U *pplane, qword normal, qword pos);
void func_002BA000(void *p);
#define XF(o) ((o)->table[36].get((char *)(o) + (o)->table[36].delta))
static __inline__ float PlaneDist(qword plane, qword pos, U *pd, U *pone)
{
    float g;
    func_002BA000(pd);
    func_002BA000(pone);
    {
        register qword one asm("vf1"); /* pin: one in vf1 */
        qword d;
        int t;
        __asm__("vmul.xyz %1, %2, %3\n\tvaddw.x %0, $vf0, $vf0w\n\tvadday.x $ACC, %1, %1y\n\tvmaddaz.x $ACC, %0, %1z\n\tvmsubw.x %1, %0, %2w"
                : "=&j"(one), "=&j"(d) : "j"(plane), "j"(pos));
        pone->q = one;
        pd->q = d;
        __asm__("qmfc2.ni %1, %2\n\tmtc1 %1, %0" : "=f"(g), "=&r"(t) : "j"(d));
    }
    return g;
}
static __inline__ float Dot(qword a, qword b)
{
    qword d, one;
    float g;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(a), "j"(b));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
    return g;
}
static __inline__ qword Sub(qword a, qword b) { qword d; __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
int func_0016E8D8(struct ST *p)
{
    struct ALO *palo = p->palo;
    int k;
    int grf;
    int n;
    float g;
    struct M4 m;
    U plane;
    if (!palo)
        return -1;
    k = palo->k250;
    n = -1;
    switch (k) {
    case 0:
        grf = p->ppo->grf1144;
        if ((grf & 0x60) == 0x60) {
            qword pl;
            U d, one;
            m = *XF(&palo->lo);
            func_00119EA8(&plane, m.r[2], m.r[3]);
            pl = plane.q;
            g = PlaneDist(pl, XF(&p->ppo->lo)->r[3], &d, &one);
            n = 3;
            if (0.0f < g)
                n = 2;
        } else if (grf & 0x20) {
            n = 2;
        } else if (grf & 0x40) {
            n = 3;
        }
        break;
    case 1:
        grf = p->ppo->grf1144;
        if ((grf & 0x180) == 0x180) {
            int f;
            float gZero = 0.0f;
            qword pl;
            qword d;
            U d1, one1;
            m = *XF(&palo->lo);
            func_00119EA8(&plane, m.r[1], m.r[3]);
            pl = plane.q;
            f = PlaneDist(pl, XF(&p->ppo->lo)->r[3], &d1, &one1) < gZero;
            d = Sub(XF(&p->ppo->lo)->r[3], m.r[3]);
            if (Dot(d, XF(&p->ppo->lo)->r[0]) < gZero)
                f = !f;
            if (f)
                n = 1;
            else
                n = 0;
        } else if (grf & 0x100) {
            n = 1;
        } else if (grf & 0x80) {
            n = 0;
        }
        break;
    }
    return n;
}
