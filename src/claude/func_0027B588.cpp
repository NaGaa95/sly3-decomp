// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// func_0027B588: wheel/suspension support contacts of a SOPART's pruned BSP. Port of Sly 2 func_001D3450 (offsets,
// callees and the geometry refresh adapted; sibling of src/leaf/wheel_support_206188.cpp). One register pin (PlaneDist2).
// Build the wheel frame (owner matrix rotation + wheel world position), prune the part's BSP to the wheel sphere, then:
//  1. edge pass: every edge between two pruned surfaces that crosses the wheel plane gives a support point (wheel space)
//     inside the wheel profile (radius circle below the axle, |x| <= radius above it);
//  2. ray pass: six segments around the wheel profile are clipped to the BSP (ClsgClipEdgeToBsp); both ends of every
//     piece give support points;
//  3. two support passes pair points by surface, find the deepest tangency of the wheel circle with each support plane,
//     and post the best one as a kind-10 contact (PxpAdd 0x1A7C18).
// Names follow the Sly 2 port (SURF/EDGE/BSP/LSG/GEOM/PvAllocStack).
typedef int qword __attribute__((mode(TI)));
typedef unsigned int uint;
typedef unsigned short ushort;

union U { qword q; float f[4]; int bits[4]; };
struct M4 { U r[4]; };
struct VECTOR4 { float x, y, z, w; };   /* BLKmode on purpose: all block locals share the sp+0x90 temp slot */

struct SCALAR;
struct VECTOR;
extern "C" SCALAR *func_002BA000(SCALAR *);
extern "C" VECTOR *func_002BA008(VECTOR *);
struct SCALAR { qword q; SCALAR() { (void)func_002BA000(this); } };
struct VECTOR { qword q; VECTOR() { (void)func_002BA008(this); } };
/* the edge-loop lerp scalars need a VF-class pseudo: qmtc2 conversion */
struct VU_FLOATQ { qword q; VU_FLOATQ(float g) { __asm__("qmtc2.ni %1,%0" : "=j"(q) : "r"(g)); } };

struct VU_VECTOR { qword q; VU_VECTOR() {} VU_VECTOR(qword v) { q = v; } };
struct EDGE { ushort aipos[2]; ushort aisurf[2]; EDGE *pedgeNext; EDGE *pedgeOtherNext; };
struct SURF { qword plane; EDGE *pedge; EDGE *pedgeOther; int grf; int ipos; };
struct BSP { BSP *pbspNeg, *pbspPos; SURF *psurf; };
struct LSG { qword apos[2]; qword anormal[2]; float au[2]; int lsgk; SURF *apsurf[2]; EDGE *pedge; int iiposSwap; LSG *plsgNext; };
struct GEOM { int cpos; qword *apos; int csurf; SURF *asurf; int cedge; EDGE *aedge; };
struct SOPART;
struct SOVT { char pad0[0xA4]; int stamp; };
struct SOPART { SOVT *pvt; char pad4[0xA0 - 4]; GEOM geomWorld; char padB8[0xC0 - 0xB8]; int stamp; };
struct SUPPORT { qword pos; SURF *apsurf[2]; int fUsed; int pad; };
struct ALLOCREQ { int cb; int cbAlign; };
struct FRAME { FRAME(); ~FRAME(); };
struct VTE { short delta, pad; M4 *(*pfn)(void *); };
struct SHAPE;
struct OWNER { char pad0[0xC]; VTE *vt; char pad10[0xD4 - 0x10]; SHAPE *shape; };
struct WHEEL { char pad0[0x14]; float radius, bottom, top; char pad20[0x20]; qword pos; };
struct CONTACT;
struct GAME;
extern GAME D_00475480;
extern const qword D_00317550;
extern const qword D_003293D0[5];
/* -FLT_MAX / FLT_MAX below are constant-pool literals (0x2A7838/0x2A783C), not globals: their REG_EQUAL sets order f24/f26 */

extern "C" {
qword func_001C9428(OWNER *, OWNER *, qword);
qword *func_002BA818(qword *, qword);
M4 func_0011D768(const M4 *);
void func_00119EA8(VECTOR4 *, qword, qword);
void *memset(void *, int, uint);
void func_0018B1E0(SOPART *);
void *PvAllocSlot(ALLOCREQ *) asm("PvAllocSlot__FP8ALLOCREQ");
int func_00119C20(BSP *, BSP *, qword, float, int *, BSP **);
int func_00119BE8(BSP *, BSP *, qword, qword, int, LSG *);
qword func_00119EF0(M4 *, qword);
void func_001CB8B0(GAME *, SHAPE *, SOPART *, qword, qword, int, int, int, CONTACT **, float);
}

static inline M4 *GetMatrix(OWNER *p) { return p->vt[36].pfn((char *)p + p->vt[36].delta); }
static inline void *PvAllocStack(int cb) { ALLOCREQ req; req.cb = cb; req.cbAlign = 0x10; return PvAllocSlot(&req); }
static inline void ClearAb(void *pv, int cb) { memset(pv, 0, cb); }
static inline float Sqrt(float f) { float r; __asm__ __volatile__("sqrt.s %0,%1" : "=&f"(r) : "f"(f)); return r; }

static inline float PlaneDist(qword plane, qword pos)
{
    SCALAR dot, one;
    qword r, unit;
    float f;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddaz.x $ACC,%1,%0z\n\tvmsubw.x %0,%1,%2w"
            : "=j"(r), "=&j"(unit) : "j"(plane), "j"(pos));
    dot.q = r;
    one.q = unit;
    __asm__("mtc1 %1,%0" : "=f"(f) : "r"(dot.q), "j"(r));   /* allocation-only "j"(r): edge-loop dot stays in a vf (sqc2 home) */
    return f;
}
static inline float PlaneDist3(qword plane, qword pos)
{
    SCALAR dot, one;
    qword r, unit;
    float f;
    int t;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddaz.x $ACC,%1,%0z\n\tvmsubw.x %0,%1,%2w"
            : "=j"(r), "=&j"(unit) : "j"(plane), "j"(pos));
    dot.q = r;
    one.q = unit;
    __asm__("qmfc2.ni %1,%2\n\tmtc1 %1,%0" : "=f"(f), "=&r"(t) : "j"(r));
    return f;
}
static inline float PlaneDist2(qword plane, qword pos)
{
    SCALAR dot, one;
    register qword r asm("vf2"); qword unit;   /* the one register pin: the dot of the second distance lives in vf2, unit in vf1 */
    float f;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddaz.x $ACC,%1,%0z\n\tvmsubw.x %0,%1,%2w"
            : "=j"(r), "=&j"(unit) : "j"(plane), "j"(pos));
    dot.q = r;
    one.q = unit;
    __asm__("mtc1 %1,%0" : "=f"(f) : "r"(dot.q), "j"(r));
    return f;
}
static inline float PlaneDistTo(qword plane, qword pos)   /* support pass: no extra ref, so point outranks plane+r (vf1/vf2) */
{
    SCALAR dot, one;
    qword r, unit;
    float f;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddaz.x $ACC,%1,%0z\n\tvmsubw.x %0,%1,%2w"
            : "=j"(r), "=&j"(unit) : "j"(plane), "j"(pos));
    dot.q = r;
    one.q = unit;
    __asm__("mtc1 %1,%0" : "=f"(f) : "r"(dot.q));
    return f;
}
static inline float Dot(qword a, qword b)
{
    qword r, one;
    float f;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(r), "=j"(one) : "j"(a), "j"(b));
    __asm__("mtc1 %1,%0" : "=f"(f) : "r"(r), "j"(r));   /* allocation-only "j"(r) (w5lane3) */
    return f;
}
/* returning the compare as a value gives the target's li 1 / move 0 setcc in this arm only */
static inline int FOutsideRadius(qword v, float r) { return r * r < Dot(v, v); }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Lerp(qword a, const VU_FLOATQ &sa, qword b, const VU_FLOATQ &sb)
{
    qword r;
    __asm__("vmulax.xyzw $ACC,%1,%2x\n\tvmaddx.xyzw %0,%3,%4x" : "=j"(r) : "j"(a), "j"(sa.q), "j"(b), "j"(sb.q));
    return r;
}
/* through a pointer: sp-based r[0] store, pointer-based for the rest, as in the target */
static inline void BuildFrame(M4 *pm, const M4 *src, qword pos)
{
    func_002BA818(&pm->r[3].q, pos);
    pm->r[0].q = src->r[0].q;
    pm->r[1].q = src->r[1].q;
    pm->r[2].q = src->r[2].q;
    pm->r[3].f[3] = 1.0f;
    pm->r[2].bits[3] = 0;
    pm->r[1].bits[3] = 0;
    pm->r[0].bits[3] = 0;
}
static inline VU_VECTOR Transform(const M4 &m, VU_VECTOR vv)
{
    qword r;
    __asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w"
            : "=j"(r) : "j"(m.r[0].q), "j"(m.r[1].q), "j"(m.r[2].q), "j"(m.r[3].q), "j"(vv.q));
    return VU_VECTOR(r);
}
static inline qword Pack(float x, float y, float z)
{
    qword q, t;
    __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0" : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z));
    return q;
}
static inline float Clamp(float v, float low, float high) { if (v < low) return low; else if (high < v) return high; else return v; }
static inline float Min(float a, float b) { return b < a ? b : a; }
/* keep VU_FLOAT's mfc1 on this line: gcse hashes asm line numbers, which orders the PRE spill slots (0xFD0..0x1000) */
struct VU_FLOAT { qword q; VU_FLOAT(float g) { __asm__("qmtc2.ni %1,%0" : "=j"(q) : "r"(g)); } };
static inline VU_VECTOR Scale(const qword &a, const VU_FLOAT &s) { qword r; __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(r) : "j"(a), "j"(s.q)); return VU_VECTOR(r); }
static inline VU_VECTOR BlendStart(const qword &a, const VU_FLOAT &sa, const qword &b, const VU_FLOAT &sb)   /* "j"(sb.q) twice: height qword VU-class -> spilled */
{
    qword r;
    __asm__("vmulax.xyzw $ACC,%2,%1x\n\tvmaddx.xyzw %0,%3,%4x" : "=j"(r) : "j"(sa.q), "j"(a), "j"(b), "j"(sb.q), "j"(sb.q));   /* 2nd "j"(sb.q): allocation-only */
    return VU_VECTOR(r);
}
static inline VU_VECTOR Blend(const qword &a, const VU_FLOAT &sa, const qword &b, const VU_FLOAT &sb)   /* in-loop: height copy below radius (vf8/vf7) */
{
    qword r;
    __asm__("vmulax.xyzw $ACC,%1,%2x\n\tvmaddx.xyzw %0,%3,%4x" : "=j"(r) : "j"(a), "j"(sa.q), "j"(b), "j"(sb.q));
    return VU_VECTOR(r);
}

extern "C" void func_0027B588(OWNER *owner, WHEEL *wheel, SOPART *ppart, int unused3, int unused4, BSP *pbspRoot, CONTACT **ppcontact)
{
    if (ppart->stamp != ppart->pvt->stamp)
        func_0018B1E0(ppart);
    int csupport = 0;
    GEOM *pgeom = &ppart->geomWorld;
    M4 *pmat = GetMatrix(owner);
    M4 frame;
    M4 *pframe = &frame;
    BuildFrame(pframe, pmat, func_001C9428(owner, 0, wheel->pos));
    M4 inverse;
    inverse = func_0011D768(pframe);
    float height = wheel->top - wheel->bottom;
    float radius = wheel->radius;
    qword plane;
    {
        VECTOR4 p;
        func_00119EA8(&p, frame.r[1].q, frame.r[3].q);
        plane = *(qword *)&p;
    }
    SUPPORT asupport[64];
    ClearAb(asupport, sizeof(asupport));
    FRAME frame_;
    LSG alsg[16];
    int cbspLeft;
    BSP *pbsp;
    BSP *absp;
    absp = pbsp = (BSP *)PvAllocStack(0x1555 * sizeof(BSP));
    cbspLeft = 0x1555;
    if (func_00119C20(pbspRoot, (BSP *)0x7FFFFFFF, frame.r[3].q, Sqrt(radius * radius + height * height), &cbspLeft, &pbsp) != 2)
        return;
    int cbsp = pbsp - absp;
    SURF *asurf = pgeom->asurf;
    pbsp--;
    int i;
    SURF *psurf;
    SUPPORT *psupport;
    for (i = 0; i < cbsp; i++) {   /* reusing i (not a new counter) puts pass+1 below &alsg in the spill slots */
        psurf = absp[i].psurf;
        psurf->grf |= 0x400;
    }
    for (i = 0; i < cbsp; i++) {
        psurf = absp[i].psurf;
        if (psurf->grf & 0x800)
            continue;
        psurf->grf |= 0x800;
        for (EDGE *pedge = psurf->pedge; pedge; pedge = pedge->pedgeNext) {
            SURF *psurfOther = &asurf[pedge->aisurf[0]];
            if (psurfOther == psurf)
                psurfOther = &asurf[pedge->aisurf[1]];
            if (!(psurfOther->grf & 0x400))
                continue;
            qword pos0 = pgeom->apos[pedge->aipos[0]];
            qword pos1 = pgeom->apos[pedge->aipos[1]];
            float d0 = PlaneDist(plane, pos0);
            float d1 = PlaneDist2(plane, pos1);
            float u = d0 / (d0 - d1);
            if (u < 0.0f || 1.0f < u)
                continue;
            VECTOR4 blend, local;
            *(qword *)&blend = Lerp(pos0, 1.0f - u, pos1, u);
            *(qword *)&local = Transform(inverse, *(qword *)&blend).q;
            if (0.0f < local.z) {
                if (radius < __builtin_fabsf(local.x))
                    continue;
            } else if (FOutsideRadius(*(qword *)&local, radius))
                continue;
            psupport = &asupport[csupport++];
            VECTOR normal;
            normal.q = plane;
            if (Dot(normal.q, Sub(pos0, pos1)) < 0.0f) {
                psupport->apsurf[1] = psurfOther;
                psupport->apsurf[0] = psurf;
            } else {
                psupport->apsurf[0] = psurfOther;
                psupport->apsurf[1] = psurf;
            }
            psupport->pos = *(qword *)&local;
        }
    }
    for (i = 0; i < cbsp; i++) {
        psurf = absp[i].psurf;
        psurf->grf &= ~0xC00;
    }
    /* ray pass. VU_VECTOR temporaries keep the loop above loop.c's ~95-insn threshold, so &D_003293D0 is not hoisted;
       posPrev = pos at the END of the body puts the a2 argument move after the row loads (sched2 tie) */
    VU_VECTOR posPrev = Transform(frame, BlendStart(D_003293D0[0], radius, D_00317550, height));
    for (uint j = 0; j < 6; j++) {
        VU_VECTOR dir;
        if (j < 5)
            dir = Scale(D_003293D0[j], radius);
        else
            dir = Blend(D_003293D0[4], radius, D_00317550, height);
        VU_VECTOR pos;
        pos = Transform(frame, dir);
        int clsg = func_00119BE8(pbsp, (BSP *)0x7FFFFFFF, posPrev.q, pos.q, 16, alsg);
        for (int k = 0; k < clsg; k++) {
            LSG *plsg = &alsg[k];
            if (plsg->apsurf[0]) {
                psupport = &asupport[csupport++];
                psupport->apsurf[1] = plsg->apsurf[0];
                psupport->pos = Transform(inverse, plsg->apos[0]).q;
            }
            if (plsg->apsurf[1]) {
                psupport = &asupport[csupport++];
                psupport->apsurf[0] = plsg->apsurf[1];
                psupport->pos = Transform(inverse, plsg->apos[1]).q;
            }
        }
        posPrev = pos;
    }
    int pass;   /* declared first: pass+1 hashes below &alsg */
    float best = 0.0f;
    qword bestPoint;
    for (pass = 0; pass < 2; pass++) {
        for (int n = 0; n < csupport; n++) {
            psupport = &asupport[n];
            float lower, upper;
            switch (pass) {   /* compare tree beqz/beq/b as in the target */
            case 0: {
                if (!psupport->apsurf[1])
                    continue;
                if (!psupport->apsurf[0])
                    lower = -3.40282347e+38f;
                else
                    lower = ((VECTOR4 *)&psupport->pos)->x;
                upper = 3.40282347e+38f;
                SUPPORT *partner = 0;
                for (int k = 0; k < csupport; k++) {
                    SUPPORT *c = &asupport[k];
                    if (c->apsurf[0] == psupport->apsurf[1]) {
                        float x = ((VECTOR4 *)&c->pos)->x;
                        if (lower < x && x < upper) {
                            upper = x;
                            partner = c;
                        }
                    }
                }
                if (partner)
                    partner->fUsed = 1;
                break;
            }
            case 1:
                if (!psupport->apsurf[0] || psupport->fUsed)
                    continue;
                lower = -3.40282347e+38f;
                if (!psupport->apsurf[1])
                    upper = 3.40282347e+38f;
                else
                    upper = ((VECTOR4 *)&psupport->pos)->x;
                break;
            }
            VECTOR4 local, point;
            *(qword *)&local = func_00119EF0(&inverse, psupport->apsurf[1 - pass]->plane);
            if (local.z < 0.0f)
                continue;
            float slope = -local.x / local.z;
            float x = Sqrt(radius * radius * slope * slope / (slope * slope + 1.0f));
            if (slope < 0.0f)
                x = -x;
            x = Clamp(x, lower, upper);
            float z = -Sqrt(radius * radius - x * x);
            point.x = x;
            point.y = 0.0f;
            point.z = z;
            float amount = Min(-PlaneDist3(*(qword *)&local, *(qword *)&point) / local.z, height);
            if (best < amount) {
                best = amount;
                VECTOR4 packed;
                *(qword *)&packed = Pack(x, 0.0f, z + best);
                bestPoint = *(qword *)&packed;
            }
        }
    }
    if (0.0f < best) {
        qword world = Transform(frame, bestPoint).q;
        VECTOR normal;
        normal.q = plane;
        func_001CB8B0(&D_00475480, owner->shape, ppart, world, normal.q, 10, 0, 0, ppcontact, best);
    }
}
