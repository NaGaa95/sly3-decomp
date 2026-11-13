// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-gcse
// func_0023E290 (Sly 3 version of the Sly 2 SO virtual func_001F50E0): rebuild the bounds record (tree) of an object from its collision parts.
// Pass 1 builds the min/max box. Visible parts only (the hidden flag skips a part); func_0023C840 first brings the part up to date, then
//   - a sphere part (flag 0x20000) adds its XF position -/+ radius * D_00317570,
//   - a part whose geometry is not built (cached version != -1) and stale against the XF (flag 0x40000 clear) adds its position -/+
//     radius * the per-axis scale of the XF matrix (column lengths) instead of building the world geometry,
//   - any other part refreshes its world geometry (func_0018B1E0) when stale and adds every world point;
//   then a part whose local points are out of date (stampGeom != stampWorld) also adds its local points moved by the part matrix.
// Pass 2 measures the sphere around the box centre ((min + max) * 0.5): a part's own radius is scaled by the XF matrix (the biggest
// axis scale, func_0011DF08, when the matrix is orthogonal, the Frobenius norm when it is skewed; sphere parts are not scaled), the
// distance centre -> sphere centre (+ own radius) or to every point extends the radius, and the own radius also grows to the farthest
// transformed local point from the XF position (stored in the part at +0xC). Finally the dirty flag D_004798E8 is set and func_0023DCF0
// is called.
// Compiler notes (what each odd-looking choice decides, all measured):
//  - -fno-gcse (as the neighbouring body/scene functions): with gcse the global copy propagation replaces the point variable p by the
//    asm output in the last loop, which turns it into a different pseudo than the other loops' p (vf1 instead of vf3 everywhere).
//  - the transformed point comes back from QwTransformPos as the VV wrapper (as in many maintained vector helpers): the copy p = VV
//    survives without gcse and gives the original "vmaddw.xyz vf2 ; vmove vf3,vf2" in the pass-2 loop (a plain qword return is
//    propagated away).
//  - the two local-point loops cache the count in n (the bound stays in one register); the world loops re-read the count.
//  - the skew test uses the qmfc2 float extraction (GFromVf), the skewed length the mtc1 extraction (F).
typedef int qword __attribute__((mode(TI)));
typedef unsigned long ulong;
union U { qword q; float f[4]; };
struct M4 { qword a, b, c, d; };
struct XF { char pad00[0x40]; union { M4 matrix; float m[4][4]; }; char pad80[0xA4 - 0x80]; int version; };
struct GEOM { int count; qword *points; int surfaceCount; void *surfaces; int edgeCount; void *edges; };
struct SOPART {
    XF *pxf; int pad04; float radius; float worldRadius;
    char pad10[8]; ulong flags;
    int first; char pad24[0xC]; M4 matrix; SOPART *next;
    char pad74[0x88 - 0x74]; GEOM local; GEOM world;
    int stampGeom, stampWorld, version;
};
struct SOTREE { qword min, max, center; float radius; SOPART *first; };
struct SO { char pad00[0xDC]; SOTREE *tree; };
struct VU_FLOAT { qword qw; };
struct VV { qword q; VV() {} VV(const qword &v) { q = v; } operator qword() const { return q; } };
extern qword D_00317570, D_00317580, D_00317590;
extern int D_004798E8;
extern "C" {
void func_0023C840(SOPART *);
void func_0018B1E0(SOPART *);
float func_0011DF08(M4 *);
void func_0023DCF0(SO *);
void func_0023E290(SO *);
}
static inline VU_FLOAT VuFloat(float g)
{
    VU_FLOAT v;
    __asm__("qmtc2.ni %1,%0" : "=j"(v.qw) : "r"(g));
    return v;
}
static inline qword QwAddScaled(qword base, qword vec, VU_FLOAT g)
{
    qword r;
    __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(base), "j"(vec), "j"(g.qw));
    return r;
}
static inline qword QwAddScaledF(qword base, qword vec, float g) { return QwAddScaled(base, vec, VuFloat(g)); }
static inline VV QwTransformPos(M4 *m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w"
            : "=j"(r) : "j"(m->a), "j"(m->b), "j"(m->c), "j"(m->d), "j"(v));
    return VV(r);
}
static inline qword QwSub(qword a, qword b)
{
    qword r;
    __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline qword QwMin(qword a, qword b)
{
    qword r;
    __asm__("vmini.xyz %0,%1,%2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline qword QwMax(qword a, qword b)
{
    qword r;
    __asm__("vmax.xyz %0,%1,%2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline float F(qword q)
{
    float g;
    __asm__("mtc1 %1,%0" : "=f"(g) : "r"(q));
    return g;
}
static inline float GFromVf(qword qw)
{
    float g;
    __asm__("qmfc2.ni %0,%1" : "=r"(g) : "j"(qw));
    return g;
}
static inline float GLength(qword d)
{
    qword one;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=&j"(one) : "0"(d));
    __asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "+j"(d));
    return F(d);
}
static inline float GDistance(const qword &a, const qword &b) { return GLength(QwSub(a, b)); }
static inline qword QwDot(qword a, qword b)
{
    qword d, one;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=j"(one) : "j"(a), "j"(b));
    return d;
}
static inline float GLengthSquared(qword v) { return F(QwDot(v, v)); }
static inline void ExtendBox(qword &lo, qword &hi, const qword &p)
{
    lo = QwMin(lo, p);
    hi = QwMax(hi, p);
}
static inline float GSqrt(float x)
{
    float r;
    __asm__ __volatile__("sqrt.s %0,%1" : "=&f"(r) : "f"(x));
    return r;
}
static inline float GAxisScale(float x, float y, float z) { return GSqrt(x * x + y * y + z * z); }
void func_0023E290(SO *pso)
{
    qword qwMin = D_00317580;
    qword qwMax = D_00317590;
    SOPART *ppart;
    int i;
    qword p;
    for (ppart = pso->tree->first; ppart; ppart = ppart->next) {
        if (ppart->flags & 0x80000UL) continue;
        func_0023C840(ppart);
        if (ppart->flags & 0x20000UL) {
            float gRadius = ppart->radius;
            qword qwLo = QwAddScaledF(*(qword *)ppart->pxf->m[3], D_00317570, -gRadius);
            qwMin = QwMin(qwMin, qwLo);
            qword qwHi = QwAddScaledF(*(qword *)ppart->pxf->m[3], D_00317570, gRadius);
            qwMax = QwMax(qwMax, qwHi);
        } else if (!(ppart->flags & 0x40000UL) && ppart->version != -1 && ppart->version != ppart->pxf->version) {
            U scale;
            float (*m)[4] = ppart->pxf->m;
            scale.f[0] = GAxisScale(m[0][0], m[1][0], m[2][0]);
            scale.f[1] = GAxisScale(m[0][1], m[1][1], m[2][1]);
            scale.f[2] = GAxisScale(m[0][2], m[1][2], m[2][2]);
            float gRadius = ppart->radius;
            qword qwLo = QwAddScaledF(*(qword *)ppart->pxf->m[3], scale.q, -gRadius);
            qwMin = QwMin(qwMin, qwLo);
            qword qwHi = QwAddScaledF(*(qword *)ppart->pxf->m[3], scale.q, gRadius);
            qwMax = QwMax(qwMax, qwHi);
        } else {
            if (ppart->version != ppart->pxf->version) func_0018B1E0(ppart);
            GEOM *pgeom = &ppart->world;
            for (i = 0; i < pgeom->count; i++) {
                p = pgeom->points[i];
                ExtendBox(qwMin, qwMax, p);
            }
        }
        if (ppart->stampWorld != ppart->stampGeom) {
            int n;
            for (i = ppart->first, n = ppart->local.count; i < n; i++) {
                p = QwTransformPos(&ppart->matrix, ppart->local.points[i]);
                ExtendBox(qwMin, qwMax, p);
            }
        }
    }
    pso->tree->min = qwMin;
    pso->tree->max = qwMax;
    VU_FLOAT gHalf = VuFloat(0.5f);
    float gRadius = 0.0f;
    qword qwCenter;
    __asm__("vmulax.xyzw $ACC,%1,%3x\n\tvmaddx.xyzw %0,%2,%3x" : "=j"(qwCenter) : "j"(qwMin), "j"(qwMax), "j"(gHalf.qw));
    for (ppart = pso->tree->first; ppart; ppart = ppart->next) {
        float gOwn = ppart->radius;
        if (!(ppart->flags & 0x20000UL)) {
            XF *pxf = ppart->pxf;
            M4 *pmat = &pxf->matrix;
            int fSkew = __builtin_fabsf(GFromVf(QwDot(pxf->matrix.a, pxf->matrix.b))) > 0.0001f || __builtin_fabsf(GFromVf(QwDot(pxf->matrix.b, pxf->matrix.c))) > 0.0001f || __builtin_fabsf(GFromVf(QwDot(pxf->matrix.a, pxf->matrix.c))) > 0.0001f;
            if (fSkew)
                gOwn *= GSqrt(GLengthSquared(pmat->a) + GLengthSquared(pmat->b) + GLengthSquared(pmat->c));
            else
                gOwn *= func_0011DF08(&pxf->matrix);
        }
        if ((ppart->flags & 0x20000UL) || (!(ppart->flags & 0x40000UL) && ppart->version != -1 && ppart->version != ppart->pxf->version)) {
            float gDist = GDistance(qwCenter, *(qword *)ppart->pxf->m[3]) + gOwn;
            if (gRadius < gDist) gRadius = gDist;
        } else {
            if (ppart->version != ppart->pxf->version) func_0018B1E0(ppart);
            GEOM *pgeom = &ppart->world;
            for (i = 0; i < pgeom->count; i++) {
                p = pgeom->points[i];
                float gDist = GDistance(qwCenter, p);
                if (gRadius < gDist) gRadius = gDist;
            }
        }
        if (ppart->stampWorld != ppart->stampGeom) {
            int n;
            for (i = ppart->first, n = ppart->local.count; i < n; i++) {
                p = QwTransformPos(&ppart->matrix, ppart->local.points[i]);
                float gDist = GDistance(qwCenter, p);
                if (gRadius < gDist) gRadius = gDist;
                gDist = GDistance(*(qword *)ppart->pxf->m[3], p);
                if (gOwn < gDist) gOwn = gDist;
            }
        }
        ppart->worldRadius = gOwn;
    }
    pso->tree->center = qwCenter;
    pso->tree->radius = gRadius;
    D_004798E8 = 1;
    func_0023DCF0(pso);
}
