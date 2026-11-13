// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Route between two points over the navigation graph (ported from Sly 2 func_001BFF28).
// Use the VU readback directly for the edge cost. The float memory operand
// keeps the target's register allocation, and the volatile store stays out of the loop branch delay slot.
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
struct V;
struct E { V *pv; volatile float cost; };
struct V { U pos; int cEdge; E *aEdge; };
struct TRI { V *apv[3]; };
struct BSP;
struct G { int pad0[3]; TRI *atri; int cv; BSP *pbsp; };
struct AREQ { int cb, align; AREQ() {} AREQ *Set(int n) { cb = n; align = 16; return this; } };
extern qword D_00317530;       // (1, 0, 0, 0)
extern "C" {
TRI *func_001EB5B0(G *, BSP *, qword, int);
qword func_001EC188(TRI *, qword);
void func_001D2770(void *);
void func_001D2798(void *, int);
void *func_001D25B0(AREQ *);
void func_001EBD50(G *, V *, V *, int, int *, V **);
void func_001EBFE8(G *, int *, V **);
int func_001EC300(G *, qword, qword, int, U *);
}
struct MARK { MARK() { func_001D2770(this); } ~MARK() { func_001D2798(this, 2); } };
static inline void StoreDistance(qword a, qword b, volatile float *out)
{
    qword d;
    __asm__("vsub.xyzw %0,%1,%2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y" : "=j"(d) : "j"(d));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(d) : "j"(d));
    __asm__("qmfc2.ni %0,%1" : "=rV"(*out) : "j"(d));
}
static inline float Dist2D(qword a, qword b)
{
    qword d; float r;
    __asm__("vsub.xyzw %0,%1,%2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y" : "=j"(d) : "j"(d));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(d) : "j"(d));
    __asm__("mtc1 %1,%0" : "=f"(r) : "r"(d));
    return r;
}
struct VU_FLOAT {
    qword q;
    VU_FLOAT(float f) { __asm__("qmtc2.ni %1,%0" : "=j"(q) : "r"(f)); }
};
static inline qword AddScaled(qword p, qword axis, VU_FLOAT s)
{
    qword r;
    __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(p), "j"(axis), "j"(s.q));
    return r;
}
int func_001EC300(G *g, qword from, qword to, int capacity, U *out)
{
    TRI *first = func_001EB5B0(g, g->pbsp, from, 1);
    if (!first) return 0;
    qword start = func_001EC188(first, from);
    TRI *last = func_001EB5B0(g, g->pbsp, to, 1);
    if (!last) return 0;
    int count;
    qword finish = func_001EC188(last, to);
    if (first == last) {
        out[0].q = from;
        out[1].q = start;
        count = 3;
        out[2].q = finish;
    } else {
        MARK mark;
        V **path = (V **)func_001D25B0(AREQ().Set(0x200));
        V initial;
        initial.pos.q = start;
        initial.cEdge = 3;
        initial.aEdge = (E *)func_001D25B0(AREQ().Set(0x18));
        for (int i = 0; i < 3; i++) {
            V *v = first->apv[i];
            E *e = &initial.aEdge[i];
            e->pv = v;
            StoreDistance(start, v->pos.q, &e->cost);
        }
        V goal;
        goal.pos.q = finish;
        goal.cEdge = 0;
        goal.aEdge = 0;
        V *pg = &goal;
        for (int i = 0; i < 3; i++) {
            V *v = last->apv[i];
            int n = v->cEdge;
            v->cEdge = n + 1;
            E *e = v->aEdge + n;
            e->pv = pg;
            StoreDistance(v->pos.q, finish, &e->cost);
        }
        int found;
        func_001EBD50(g, &initial, pg, 128, &found, path);
        if (found >= 3) func_001EBFE8(g, &found, path);
        int n = found;
        if (n > capacity) n = capacity;
        count = n;
        for (int i = 0; i < count; i++) out[i].q = path[i]->pos.q;
        for (int i = 0; i < 3; i++) last->apv[i]->cEdge--;
    }
    {
        U *end = out + count;
        U *rd = out + 1;
        U *wr = out + 1;
        qword prev = out[0].q;
        if (wr < end) {
            do {
                if (50.0f < Dist2D(rd->q, prev)) {
                    U *s = rd++;
                    U *d = wr++;
                    prev = s->q;
                    d->q = prev;
                } else rd++;
            } while (rd < end);
        }
        count = wr - out;
    }
    if (count == 1) {
        count = 2;
        VU_FLOAT s(50.0f);
        qword p = out[0].q;
        out[1].q = p;
        out[0].q = AddScaled(p, D_00317530, s);
    }
    return count;
}
