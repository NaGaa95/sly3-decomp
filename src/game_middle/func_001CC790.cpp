// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Edge/edge and vertex/face contacts between two clipped collision shapes (Sly 3 version of the Sly 2 function src/hand/func_001A8B50.cpp).
// func_001CBD18 / func_001CBE38 clip each shape's edges against the other, func_001CC068 sorts the clipped segments of each side,
// func_001CC440 adds the vertex contacts of both sides; then every free segment of side 0 either follows the func_001CC2F0 edge path of
// side 1 (closest points of the two edges via func_00120658, contact kind 3) or, when no side-1 segment shares a surface with its edge,
// contacts the nearer edge end against the farther plane (kind 1). With no new contact and one side empty a kind-13 contact at the shape
// position is added.
// Sly 3 differences from the Sly 2 source: both shapes refresh their cached geometry lazily (func_0018B1E0) before it is read, the
// reference point of the plane distances is the shape's first transformed point (ShapePosInto), and the vertex contacts come from func_001CC440.
// Source-shape notes: the function-level arrays, the by-value VV / VU_FLOAT helper parameters (struct copies that keep the dead stores of the
// original) and the PlaneDist parameter order of the first two distances decide slot offsets and register numbers; the position is a memory
// object (U posU) because it is re-read after the SCALAR constructor calls.
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
struct VV { qword q; VV() {} VV(const qword &v) { q = v; } operator qword() const { return q; } };
struct SCALAR;
extern "C" SCALAR *func_002BA000(SCALAR *);
struct SCALAR { qword q; SCALAR() { (void)func_002BA000(this); } };
struct SCENE;
struct CONTACT;
struct SPACE { char pad0[0x70]; U position; char pad80[0x24]; int version; };
struct EDGE { unsigned short aipos[2], aisurf[2]; EDGE *pedgeNext; EDGE *pedgeOtherNext; };
struct SURF { U plane; EDGE *pedge; EDGE *pedgeOther; unsigned int grf; int ipos; };
struct GEOM { int cpos; U *apos; int csurf; SURF *asurf; int cedge; EDGE *aedge; };
struct M4 { qword r[4]; };
struct SHAPE {
    SPACE *space;                   // 0x00
    char pad04[0x20 - 4];
    int iFirst;                     // 0x20
    char pad24[0x30 - 0x24];
    M4 xf;                          // 0x30 (translation row at 0x60)
    char pad70[0x88 - 0x70];
    int cpoint;                     // 0x88
    U *apoint;                      // 0x8C
    char pad90[0xA0 - 0x90];
    GEOM geom;                      // 0xA0
    char padB8[0xC0 - 0xB8];
    int version;                    // 0xC0
};
struct NODE { unsigned int left, right; SURF *psurf; };
struct LSG { U apos[2], anormal[2]; float au[2]; int lsgk; SURF *apsurf[2]; EDGE *pedge; int iiposSwap; LSG *plsgNext; };
struct XP { char pad0[0x9C]; int kind; void *first, *second; int padA8; XP *next; };
extern "C" {
extern qword D_00317550;
void func_0018B1E0(SHAPE *);
int func_001CBD18(SCENE *, SHAPE *, SHAPE *, NODE *, int, LSG *);
int func_001CBE38(SCENE *, SHAPE *, SHAPE *, int, NODE *, int, LSG *);
void func_001CC068(int, LSG *, int *, int *, LSG **, LSG **);
void func_001CC440(SCENE *, SHAPE *, SHAPE *, int, int *, LSG **, CONTACT **);
int func_001CC2F0(SURF *, int, int, LSG *, LSG **);
int func_00120658(qword, qword, qword, qword, float *, U *);
void func_001CB8B0(SCENE *, SHAPE *, SHAPE *, VV, float, VV, int, void *, void *, CONTACT **);
}
static inline GEOM *GeomOf(SHAPE *s)
{
    if (s->version != s->space->version)
        func_0018B1E0(s);
    return &s->geom;
}
static inline qword MulMatVec(const M4 *pm, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %1, %5x\n\tvmadday.xyz $ACC, %2, %5y\n\tvmaddaz.xyz $ACC, %3, %5z\n\tvmaddw.xyz %0, %4, $vf0w"
            : "=j"(r) : "j"(pm->r[0]), "j"(pm->r[1]), "j"(pm->r[2]), "j"(pm->r[3]), "j"(v));
    return r;
}
static inline void ShapePosInto(SHAPE *s, U *out)
{
    if (s->iFirst < s->cpoint)
        out->q = MulMatVec(&s->xf, s->apoint[s->iFirst].q);
    else
        out->q = s->xf.r[3];
}
static inline VV Sub(VV a, VV b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
struct VU_FLOAT { qword qw; };
static inline VU_FLOAT VuFloat(float g)
{
    VU_FLOAT v;
    __asm__("qmtc2.ni %1,%0" : "=j"(v.qw) : "r"(g));
    return v;
}
static inline VV QwMix(VU_FLOAT g1, VV qw1, VU_FLOAT g2, VV qw2)
{
    qword qw;
    __asm__("vmulax.xyzw $ACC,%1,%3x\n\tvmaddx.xyzw %0,%2,%4x" : "=j"(qw) : "j"(qw1), "j"(qw2), "j"(g1.qw), "j"(g2.qw));
    return qw;
}
/* gcc supplies the qmfc2 for the "r" operand; the repeated "j" operand is allocation-only (keeps the value VU class). */
static inline float GFromVf(VU_FLOAT v) { float g; __asm__("mtc1 %1,%0" : "=f"(g) : "r"(v.qw), "j"(v.qw)); return g; }
static inline float Length(VV v)
{
    VV d, one;
    VU_FLOAT len;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(d) : "j"(d));
    len.qw = d;
    return GFromVf(len);
}
/* signed distance of a point from a plane: dot(plane.xyz, point.xyz) - plane.w */
static inline float PlaneDist(VV plane, VV point)
{
    SCALAR dot, one;
    qword r, unit;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddaz.x $ACC,%1,%0z\n\tvmsubw.x %0,%1,%2w"
            : "=j"(r), "=&j"(unit) : "j"(plane.q), "j"(point));
    dot.q = r;
    one.q = unit;
    VU_FLOAT g;
    g.qw = dot.q;
    return GFromVf(g);
}
/* the same distance for the endpoint contact: the point is the first argument here, and the register number of the result is pinned */
static inline float PlaneDistAt(VV point, VV plane)
{
    SCALAR dot, one;
    register qword r __asm__("vf2"); /* register pin: the squared-length VU register of this distance is vf2 like the original */
    qword unit;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddaz.x $ACC,%1,%0z\n\tvmsubw.x %0,%1,%2w"
            : "=j"(r), "=&j"(unit) : "j"(plane.q), "j"(point));
    dot.q = r;
    one.q = unit;
    VU_FLOAT g;
    g.qw = dot.q;
    return GFromVf(g);
}
static inline void Closest(VV a, VV b, VV c, VV d, float *au, U *normal)
{
    (void)func_00120658(a, b, c, d, au, normal);
}

extern "C" void func_001CC790(SCENE *scene, SHAPE *a, SHAPE *b, int nodeCount, NODE *nodes, NODE *last, CONTACT **out)
{
    int aclsg[2];
    LSG aalsg[2][128];
    int acpos[2];
    int aaipos[2][128];
    LSG *aaplsg[2][128];
    LSG *aplsgBoth[2];
    LSG *aplsgPath[32];
    float au[2];
    U normal;
    U apos[2];
    CONTACT *old = *out;
    GEOM *pgeomA = GeomOf(a);
    GEOM *pgeomB = GeomOf(b);
    aclsg[0] = func_001CBD18(scene, b, a, last, 128, aalsg[0]);
    int clsg1 = func_001CBE38(scene, a, b, nodeCount, nodes, 128, aalsg[1]);
    aclsg[1] = clsg1;
    if (!aclsg[0] && !clsg1)
        return;
    {
        int i;
        for (i = 0; i < 2; i++)
            func_001CC068(aclsg[i], aalsg[i], &acpos[i], aaipos[i], aaplsg[i], &aplsgBoth[i]);
    }
    func_001CC440(scene, a, b, acpos[0], aaipos[0], aaplsg[0], out);
    func_001CC440(scene, b, a, acpos[1], aaipos[1], aaplsg[1], out);
    for (LSG *plsg = aplsgBoth[0]; plsg; plsg = plsg->plsgNext) {
        int both = plsg->apsurf[0] && plsg->apsurf[1];
        if (!both)
            continue;
        int clsgPath = func_001CC2F0(pgeomB->asurf, plsg->apsurf[0] - pgeomB->asurf, plsg->apsurf[1] - pgeomB->asurf, aplsgBoth[1], aplsgPath);
        if (clsgPath > 0) {
            int j;
            for (j = 0; j < clsgPath; j++) {
                LSG *plsgOther = aplsgPath[j];
                qword left0 = pgeomA->apos[plsg->pedge->aipos[0]].q, left1 = pgeomA->apos[plsg->pedge->aipos[1]].q;
                qword right0 = pgeomB->apos[plsgOther->pedge->aipos[0]].q, right1 = pgeomB->apos[plsgOther->pedge->aipos[1]].q;
                Closest(left0, left1, right0, right1, au, &normal);
                apos[0].q = QwMix(VuFloat(1.0f - au[0]), left0, VuFloat(au[0]), left1);
                apos[1].q = QwMix(VuFloat(1.0f - au[1]), right0, VuFloat(au[1]), right1);
                float g = -Length(Sub(apos[0].q, apos[1].q));
                func_001CB8B0(scene, a, b, apos[0].q, g, normal.q, 3, plsg->pedge, plsgOther->pedge, out);
            }
            continue;
        }
        int i;
        for (i = 0; i < aclsg[1]; i++) {
            LSG *plsgOther = &aalsg[1][i];
            if (plsgOther->apsurf[0] == pgeomA->asurf + plsg->pedge->aisurf[0] || plsgOther->apsurf[0] == pgeomA->asurf + plsg->pedge->aisurf[1] ||
                plsgOther->apsurf[1] == pgeomA->asurf + plsg->pedge->aisurf[0] || plsgOther->apsurf[1] == pgeomA->asurf + plsg->pedge->aisurf[1])
                goto next;
        }
        {
            U posU;
            ShapePosInto(a, &posU);
            float g0 = PlaneDist(plsg->anormal[0].q, posU.q);
            float g1 = PlaneDist(plsg->anormal[1].q, posU.q);
            SURF *psurf;
            int ipos;
            if (g1 < g0) {
                ipos = 1 - plsg->iiposSwap;
                psurf = plsg->apsurf[0];
            } else {
                ipos = plsg->iiposSwap;
                psurf = plsg->apsurf[1];
            }
            U *ppos = pgeomA->apos + plsg->pedge->aipos[ipos];
            XP *pxp = (XP *)*out;
            while (pxp) {
                if (pxp->kind == 1 && pxp->first == ppos && pxp->second == psurf)
                    break;
                pxp = pxp->next;
            }
            if (pxp)
                continue;
            qword pos = ppos->q, plane = psurf->plane.q;
            float g = PlaneDistAt(pos, plane);
            func_001CB8B0(scene, a, b, pos, g, plane, 1, ppos, psurf, out);
        }
    next:;
    }
    if (old == *out && (!aclsg[0] || !aclsg[1]))
        func_001CB8B0(scene, a, b, a->space->position.q, 0.0f, D_00317550, 13, 0, 0, out);
}
