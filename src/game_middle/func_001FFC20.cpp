// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_001FFC20 and func_00200F50 share one translation unit and therefore one .rodata block (0x325690..0x3256B0): the 24-byte jump table
// of func_001FFC20 followed by the FLT_MAX pair that the compiler emits for func_00200F50's bounding-box initialisation.
// func_001FFC20: emitter direction generator (companion of func_001FF6B0): fills out->advs by kindDir (0 = the normalised axis,
// 1 = normalised apos[i] - axis, 4 = normalised transform of the axis through the camera object, 2/3/5 keep the directions the position
// generator already produced for mesh emitters, otherwise the default direction), scales the positions by a random speed, then spreads
// the directions over a cone (random angle/elevation, rotated into the direction frame).
// func_00200F50: CPU fallback of the particle batch update (func_00201948 is the microprogram variant): for every batch in the list at p->dl it copies the
// live particles (b.w > clock time) from the current buffer to the other one (velocity transformed by the emitter matrix, plain copy, or a
// stepper call), accumulates the bounding box and finally sets the bounding sphere; returns 1 while particles remain, 0 otherwise.
// Based on Sly 2 func_00139DC0.
typedef int qword __attribute__((mode(TI)));
#define FLT_MAX 3.40282347e+38f
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j,j"(q) : "r,m"(f), "i,r"(0)); } };
static inline qword AddScaled(qword a, qword b, VU_FLOAT s)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(b), "j"(s.q));
    return r;
}
static inline qword Min(qword a, qword b) { qword r; __asm__("vmini.xyz %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Max(qword a, qword b) { qword r; __asm__("vmax.xyz %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Mid(qword a, qword b, VU_FLOAT h)
{
    qword c;
    __asm__("vmulax.xyzw $ACC, %1, %3x\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(c) : "j"(a), "j"(b), "j"(h.q));
    return c;
}
static inline qword QwSub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword QwLength(qword v)
{
    qword qw, one;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(qw), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(qw) : "j"(qw));
    return qw;
}
static inline float GFromQw(qword q) { float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(q)); return g; }
static inline qword MulPoint(const qword *pm, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %1, %5x\n\tvmadday.xyz $ACC, %2, %5y\n\tvmaddaz.xyz $ACC, %3, %5z\n\tvmaddw.xyz %0, %4, $vf0w"
            : "=j"(r) : "j"(pm[0]), "j"(pm[1]), "j"(pm[2]), "j"(pm[3]), "j"(v));
    return r;
}
struct M4 { qword r[4]; };
struct VECTOR { union { struct { float x, y, z; } v; qword q; }; };
struct VEC { union { qword q; struct { float x, y, z, w; } v; }; };

struct DL { void *head; void *tail; int ibDle; };
struct DLI { DL *m_pdl; void **m_ppv; int m_ibDle; DLI *m_pdliNext; };
// Particle batch: positions (a), velocities with end time in w (b), per-particle records (c)
struct BUF { VEC a[0x2B]; VEC b[0x2B]; VEC c[0x2B]; char pad[0x840 - 0x810]; };
struct E { qword v0; qword v10; };
struct Q { BUF abuf[2]; int i; int c; E *ae; };
struct Shape { char pad0[0x24]; int k24; int k28; };
struct Kind { char pad0[0x1C]; Shape *shape; };
struct PX {
    int pad0; Kind *kind; char pad8[0x2C - 8]; float radius; qword centre; char pad40[0x50 - 0x40]; DL dl; int count; char pad60[0x80 - 0x60]; float extent;
    char pad84[0xC0 - 0x84]; char xC0[1];
};
struct CLOCK { float t; float dt; };
// The copies and the bounding box read the a/b lanes through the c pointers (the compiler's induction variable base)
#define CA(p) ((VEC *)((int)(p) - 0x560))
#define CB(p) ((VEC *)((int)(p) - 0x2B0))
extern "C" {
extern CLOCK D_0036BB98;
extern DLI *D_0036AE94;
extern int D_00342DB0;
int func_0011B0F0(DL *pdl);
void func_00201E18(PX *p);
M4 func_00179CC0(void *p);
int func_00201948(PX *p, M4 *pm);
void func_00118558(float, float, float, qword, qword, qword, qword, qword *, qword *, int);
float func_0011E3B8(float g);
void func_001495F8(Q *pq);
int func_00200F50(PX *p);
}

static inline void InitDli(DLI *pdli, DL *pdl)
{
    pdli->m_pdl = pdl;
    pdli->m_ppv = (void **)pdl;
    pdli->m_ibDle = pdl->ibDle;
    pdli->m_pdliNext = D_0036AE94;
    D_0036AE94 = pdli;
}
static inline void *PvNextDli(DLI *pdli)
{
    void *pv = *pdli->m_ppv;
    pdli->m_ppv = (void **)((char *)pv + pdli->m_ibDle);
    return pv;
}

struct VU_VECTOR { qword q; };
union U { qword q; float f[4]; };
struct M3 { qword r[3]; };
struct VTE { short delta, pad; void *fn; };
struct OBJ { char pad0[0xC]; VTE *vt; };
struct EP { char pad0[0x30]; qword v30; float x40, x44; int kind; int kindDir; };
struct EP2 { char pad0[0x40]; float x40, x44, x48, x4C; char pad50[0x1C]; float x6C; char pad70[4]; float x74; };
struct NODE { char pad0[0x14]; void *p14; };
struct EMIT { NODE *pnode; struct { char pad[0x10]; EP *pep; EP2 *pep2; } *pdata; };
struct OUT { int count; qword *apos; qword *advs; };
extern char D_00475480[];
extern qword D_00317530, D_00317540;
extern "C" {
float func_0011E940(float gMin, float gMax);
float func_0011E3B8(float);
qword func_0011FDD8(float, float, float);
void func_0011FEA8(qword, qword, qword, M3 *);
OBJ *func_00165B28(void *);
qword func_001C94E8(OBJ *, void *, qword);
}
static inline VU_VECTOR V(qword q) { VU_VECTOR v; v.q = q; return v; }
static inline qword Sub(qword a, qword b) { qword d; __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
static inline qword Add(VU_VECTOR a, qword b) { qword d; __asm__("vadd.xyzw %0, %1, %2" : "=j"(d) : "j"(a.q), "j"(b)); return d; }
static inline qword Scale(VU_FLOAT f, VU_VECTOR v) { qword r; __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(r) : "j"(f.q), "j"(v.q)); return r; }
static inline qword MulMat(const M3 &m, qword v)
{
    qword d;
    __asm__("vmulax.xyz $ACC, %2, %1x\n\tvmadday.xyz $ACC, %3, %1y\n\tvmaddz.xyz %0, %4, %1z"
            : "=j"(d) : "j"(v), "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]));
    return d;
}
static inline qword VLen(qword c)
{
    qword l, one;
    __asm__("vmul.xyz %1, %2, %2\n\tvaddw.x %0, $vf0, $vf0w\n\tvadday.x $ACC, %1, %1y\n\tvmaddz.x %1, %0, %1z" : "=j"(one), "=&j"(l) : "j"(c));
    qword r;
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(r) : "j"(l));
    return r;
}
static inline VU_VECTOR Normalize(qword d)
{
    VU_VECTOR dir;
    qword l = VLen(d);
    VU_VECTOR k;
    k.q = D_00317530;
    if (GFromQw(l) < 0.0001f) {
        dir = k;
    } else {
        qword dq;
        __asm__("vdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(dq) : "j"(d), "j"(l));
        dir.q = dq;
    }
    return dir;
}
static inline qword *Matrix36(OBJ *o) { VTE *e = &o->vt[36]; return ((qword *(*)(void *))e->fn)((char *)o + e->delta); }
extern "C" void func_001FFC20(EMIT *p, OUT *out)
{
    EP *ep = p->pdata->pep;
    EP2 *ep2 = p->pdata->pep2;
    switch (ep->kindDir) {
    case 0:
        for (int i = 0; i < out->count; i++)
            out->advs[i] = Normalize(ep->v30).q;
        break;
    case 1:
        for (int i = 0; i < out->count; i++)
            out->advs[i] = Normalize(Sub(out->apos[i], ep->v30)).q;
        break;
    case 4: {
        M3 mat;
        mat = *(M3 *)Matrix36(func_00165B28(D_00475480));
        for (int i = 0; i < out->count; i++)
            out->advs[i] = Normalize(func_001C94E8(func_00165B28(D_00475480), p->pnode->p14, ep->v30)).q;
        break;
    }
    case 2:
    case 3:
        if (ep->kind == 2)
            break;
        goto fill;
    case 5:
        if (ep->kind == 3)
            break;
    default:
    fill:
        for (int i = 0; i < out->count; i++)
            out->advs[i] = D_00317530;
        break;
    }
    if (ep->x40 != 0.0f || ep->x44 != 0.0f) {
        for (int i = 0; i < out->count; i++) {
            qword *pa = (qword *)(i * 16 + (long)out->apos);
            VU_VECTOR pv = V(*pa);
            VU_VECTOR dv = V(out->advs[i]);
            float g = func_0011E940(ep->x40, ep->x44);
            *pa = Add(pv, Scale(g, dv));
        }
    }
    float step = 6.2831855f / (float)out->count;
    float range = ep2->x4C - ep2->x48;
    float az = func_0011E940(0.0f, 6.2831855f);
    float el0 = ep2->x48 + range * 0.5f + 1.5707964f;
    for (int i = 0; i < out->count; i++) {
        float a = az, e = el0;
        if (ep2->x74 != 0.0f) {
            a = az + ep2->x74 * func_0011E940(-0.5f, 0.5f) * step;
            e = e + ep2->x74 * func_0011E940(-0.5f, 0.5f) * range;
        }
        float wa = func_0011E3B8(a);
        float we = func_0011E3B8(e);
        az += step;
        U vec;
        vec.q = func_0011FDD8(wa, we, func_0011E940(ep2->x40, ep2->x44));
        vec.f[2] *= ep2->x6C;
        M3 m;
        m.r[2] = out->advs[i];
        func_0011FEA8(m.r[2], D_00317530, D_00317540, &m);
        out->advs[i] = MulMat(m, vec.q);
    }
}

int func_00200F50(PX *p)
{
    M4 m;
    if (func_0011B0F0(&p->dl))
        return 0;
    func_00201E18(p);
    Shape *pshape = p->kind->shape;
    int kind = pshape->k28;
    int k24 = pshape->k24;
    if (kind == 0) {
        m = func_00179CC0(p->xC0);
        if (D_00342DB0 == 0)
            return func_00201948(p, &m);
    }
    {
    VECTOR vMin = {{{FLT_MAX, FLT_MAX, FLT_MAX}}};
    VECTOR vMax = {{{-FLT_MAX, -FLT_MAX, -FLT_MAX}}};
    DLI dli;
    Q *pq;
    InitDli(&dli, &p->dl);
    while ((pq = (Q *)PvNextDli(&dli)) != 0) {
        int cDead, iNext, j, i;
        BUF *pb, *pbn;
        j = 0;
        cDead = 0;
        pb = &pq->abuf[pq->i];
        iNext = (pq->i + 1) & 1;
        pbn = &pq->abuf[iNext];
        for (i = 0; i < pq->c; i++) {
            float t = D_0036BB98.t;
            float tEnd = pb->a[i + 43].v.w;
            if (tEnd <= t) {
                cDead++;
                continue;
            }
            switch (kind) {
            case 0: {
                qword v = MulPoint(m.r, pb->a[i + 43].q);
                pbn->a[j + 43].q = v;
                pbn->a[j].q = AddScaled(pb->a[i].q, v, VU_FLOAT(D_0036BB98.dt));
                break;
            }
            case 1: {
                qword v = pb->a[i + 43].q;
                pbn->a[j + 43].q = v;
                pbn->a[j].q = AddScaled(pb->a[i].q, v, VU_FLOAT(D_0036BB98.dt));
                break;
            }
            case 2: {
                float rem = tEnd - t;
                float dt = D_0036BB98.dt;
                func_00118558(rem, dt < rem ? dt : rem, 1.0f, pb->a[i].q, pb->a[i + 43].q, pq->ae[i].v0, pq->ae[i].v10, &pbn->a[j].q, &pbn->a[j + 43].q, 0);
                if (j != i)
                    pq->ae[j] = pq->ae[i];
                break;
            }
            }
            {
            VEC *pcs = &pb->c[i];
            VEC *pcd = &pbn->c[j];
            CA(pcd)[0].v.w = CA(pcs)[0].v.w;
            CB(pcd)[0].v.w = CB(pcs)[0].v.w;
            *pcd = *pcs;
            if (k24 == 2)
                pcd->v.w = func_0011E3B8(pcs->v.w + pcs->v.z * D_0036BB98.dt);
            vMin.q = Min(vMin.q, CA(pcd)[0].q);
            vMax.q = Max(vMax.q, CA(pcd)[0].q);
            }
            j++;
        }
        pq->c -= cDead;
        p->count -= cDead;
        if (!pq->c)
            func_001495F8(pq);
        else
            pq->i = iNext;
    }
    if (p->count > 0) {
        qword c = Mid(vMin.q, vMax.q, VU_FLOAT(0.5f));
        p->centre = c;
        float g = GFromQw(QwLength(QwSub(c, vMax.q)));
        p->radius = g + p->extent;
        D_0036AE94 = dli.m_pdliNext;
        return 1;
    }
    D_0036AE94 = dli.m_pdliNext;
    return 0;
    }
}
