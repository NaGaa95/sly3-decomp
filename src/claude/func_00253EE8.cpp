// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sly3 PloGuardTarget-style pick (cf Sly2 PloGuardTarget3F 0x14B290): best (class rank, distance) target; returns {k, plo}. Unit rodata 0x327400/0x327410 defined as statics.
typedef int qword __attribute__((mode(TI)));
struct VTE { short delta; short pad; void *(*method)(void *); };
struct POSQ { char pad[0x30]; qword pos; };
typedef unsigned int DI __attribute__((mode(DI)));
struct LO { char pad[0xC]; struct VTE *vt; char pad10[0x28 - 0x10]; DI lo : 56; DI bits : 8; };
struct E { struct LO *po; int n4; int fOn; int pad[2]; };
struct L { char pad[0xD8]; int c; struct E ae[1]; };
struct P { char pad[0xC]; struct VTE *vt; char pad10[0x3AC - 0x10]; struct LO *p3AC; struct LO *p3B0;
    char pad3B4[0x10D0 - 0x3B4]; struct L *pl; };
struct RES { int k; struct LO *po; };
struct CTX { int a; CTX(); ~CTX(); };
struct ALLOCREQ { int cb; int cbAlign; };
extern "C" {
extern char D_00475480[];
int func_00257F28(struct P *p);
int func_0017E208(void *, int, int, int, int, struct LO **);
void *PvAllocSlot__FP8ALLOCREQ(struct ALLOCREQ *);
int func_002544E0(struct P *p, struct LO *po);
struct RES func_00253EE8(struct P *p);
}
static inline void *PvAllocMsg(ALLOCREQ *pmsg, int cb, int nKind) { pmsg->cb = cb; pmsg->cbAlign = nKind; return PvAllocSlot__FP8ALLOCREQ(pmsg); }
#define VCALL(po, n) ((po)->vt[n].method((char *)(po) + (po)->vt[n].delta))
static const float RO_FLT_00327400[4] = { -400.0f, 0.8f, 0.0f, 0.0f };
static const float RO_FLT_00327410[2] = { 3.40282346638528859812e+38f, 0.0f };
static inline bool FBit(struct LO *po) { return (int)po->bits & 1; }
static __inline__ float GDist(qword a, qword b)
{
    qword d, t;
    float g;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xyz %0, %0, %0\n"
        "vaddw.x %1, $vf0, $vf0w\n"
        "vadday.x ACC, %0, %0y\n"
        "vmaddz.x %0, %1, %0z" : "+j"(d), "=j"(t));
    __asm__("vsqrt Q, %0x\n"
        "vwaitq\n"
        "vaddq.x %0, $vf0, Q" : "+j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
    return g;
}
struct RES func_00253EE8(struct P *p)
{
    struct LO *poBest = 0;
    int kBest = -1;
    struct LO *po = p->p3B0;
    if (po && FBit(po)) {
        poBest = po;
        kBest = 2;
    } else {
        float gBest = RO_FLT_00327410[0];
        int c = 0;
        int dBest = 999;
        struct E *ae;
        int i;
        qword pos = ((struct POSQ *)VCALL(p, 36))->pos;
        CTX ctx;
        if (func_00257F28(p)) {
            struct LO *apo[16];
            ALLOCREQ req;
            int n = func_0017E208(D_00475480, 0x105, 0x3A, 0, 0x10, apo);
            int j;
            ae = (struct E *)PvAllocMsg(&req, n * 0x14, 0x10);
            for (j = 0; j < n; j++) {
                struct LO *o = apo[j];
                if (o != (struct LO *)p) {
                    struct E *e = &ae[c++];
                    e->fOn = 1;
                    e->po = o;
                    e->n4 = 0;
                }
            }
        } else {
            c = p->pl->c;
            ae = p->pl->ae;
        }
        for (i = 0; i < c; i++) {
            struct E *e = &ae[i];
            struct LO *po;
            int k, d;
            float g;
            if (!e->fOn) continue;
            po = e->po;
            if (!FBit(po)) continue;
            k = func_002544E0(p, po);
            d = e->n4;
            if (k < kBest) continue;
            if (k == kBest && dBest < d) continue;
            g = GDist(pos, ((struct POSQ *)VCALL(po, 36))->pos);
            if (po == p->p3AC)
                g = RO_FLT_00327400[0] + g * (RO_FLT_00327400[1] + g * RO_FLT_00327400[2]);
            if (kBest < k || d < dBest || g < gBest) {
                poBest = po;
                dBest = d;
                kBest = k;
                gBest = g;
            }
        }
    }
    {
        struct RES r;
        r.k = kBest;
        r.po = poBest;
        return r;
    }
}
