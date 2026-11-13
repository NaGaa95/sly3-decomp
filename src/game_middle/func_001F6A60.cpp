// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Finds the deepest contact and applies a position correction and velocity response.
typedef int qword __attribute__((mode(TI)));
union U { qword qw; float g[4]; };
struct VTE { short delta, pad; void *fn; };
struct XF { char pad[0x70]; qword pos; };
struct PSO { char pad0[0x10]; PSO *parent; char pad14[0x128 - 0x14]; unsigned long flags; };
struct SOPART { XF *pxf; PSO *pso; float sRadius; char padC[0xC]; unsigned long grf; char pad20[0x64]; int cplane; };
struct CMCONTACT { qword pos; U plane; int kind; void *pv; };
union FW { float g; int bits; };
struct P {
    char pad0[0xC]; VTE *vt; char pad10[0x130 - 0x10]; int state; char pad134[0x170 - 0x134]; int enabled;
    float gThreshold; FW gBoost; float sRadius; float gNormalResponse; FW gTangent; SOPART *hit;
};
class FRAME;
extern "C" {
extern char D_00475480[];
extern qword D_00317530, D_00317550, D_00317560, D_00317570;
void func_001D2770(FRAME *);
void func_001D2798(FRAME *, int);
int func_001F69F8(void *, SOPART *);
void func_0025CF18(void *, qword, qword, int (*)(void *, SOPART *), void *, int *, SOPART ***);
int func_001CD098(qword, float, SOPART *, void *, int, void *, int, CMCONTACT *);
float func_0011FE60(qword, qword, qword *, qword *);
qword func_0028BCD0(XF *, int, qword);
}
class FRAME { public: FRAME() { func_001D2770(this); } ~FRAME() { func_001D2798(this, 2); } };
struct VU_FLOAT {
    qword qw;
    VU_FLOAT(float g) { __asm__("qmtc2.ni %1, %0" : "=j"(qw) : "r"(g)); }
    VU_FLOAT(int bits) { __asm__("qmtc2.ni %1, %0" : "=j"(qw) : "rV"(bits)); }
};
static inline qword VuFloat(float g) { qword r; __asm__("qmtc2.ni %1, %0" : "=j"(r) : "r"(g)); return r; }
static inline float GFromQw(qword q) { float g; __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(q)); return g; }
static inline float GFromVf(qword q) { float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(q), "j"(q)); return g; }
static inline float GFromQ(qword q) { float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(q)); return g; }
static inline qword QwAddScaled(qword base, qword dir, qword g)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(base), "j"(dir), "j"(g));
    return r;
}
static inline qword QwCombo(VU_FLOAT g1, qword v1, VU_FLOAT g2, qword v2)
{
    qword r;
    __asm__("vmulax.xyzw $ACC, %2, %1x\n\tvmaddx.xyzw %0, %4, %3x" : "=j"(r) : "j"(g1.qw), "j"(v1), "j"(g2.qw), "j"(v2));
    return r;
}
static inline qword QwSub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword QwZero() { qword r; __asm__("vsub.xyzw %0, $vf0, $vf0" : "=j"(r)); return r; }
static inline qword QwAdd(qword a, qword b) { qword r; __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword QwLength(qword v)
{
    qword d, one, len;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=&j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(len) : "j"(d));
    return len;
}
static inline qword QwUnit(qword v, qword len)
{
    qword r;
    __asm__("vdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(r) : "j"(v), "j"(len));
    return r;
}
static inline qword QwNormalize(qword v, qword fallback)
{
    qword len = QwLength(v);
    if (GFromQw(len) < 0.0001f)
        return fallback;
    return QwUnit(v, len);
}
static inline qword QwNormalizeInto(qword *pv, const qword &fallback)
{
    qword v = *pv;
    qword len = QwLength(v);
    if (GFromVf(len) < 0.0001f)
        *pv = fallback;
    else
        *pv = QwUnit(v, len);
    return len;
}
static inline float GDot(qword a, qword b)
{
    qword d, one;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(a), "j"(b));
    return GFromVf(d);
}
/* Keep the value in a VU register; this allocation constraint emits no instruction. */
static inline qword QwVu(qword v) { qword r; __asm__ volatile("" : "=j"(r) : "0"(v)); return r; }
static inline float GMin(float a, float b) { return (b < a) ? b : a; }
static inline qword Position(P *p) { VTE *e = &p->vt[36]; return ((qword *(*)(void *))e->fn)((char *)p + e->delta)[3]; }
static inline qword Velocity(P *p) { VTE *e = &p->vt[38]; return ((qword (*)(void *))e->fn)((char *)p + e->delta); }
static inline void SetPosition(P *p, qword q) { VTE *e = &p->vt[34]; ((void (*)(void *, qword))e->fn)((char *)p + e->delta, q); }
static inline void SetVelocity(P *p, qword q) { VTE *e = &p->vt[40]; ((void (*)(void *, qword))e->fn)((char *)p + e->delta, q); }

extern "C" void func_001F6A60(P *p)
{
    if (p->enabled) {
        float gDeepest = 0.0f;
        int i = 0;
        qword relVel;
        qword pos = Position(p);
        qword vel = Velocity(p);
        __asm__("" : "+r"(vel)); /* Preserve the velocity across frame construction. */
        FRAME frame;
        relVel = vel;
        U vec;
        qword posMin = (vec.qw = VuFloat(-p->sRadius), QwAddScaled(pos, D_00317570, vec.qw));
        qword posMax = QwAddScaled(pos, D_00317570, (vec.qw = VuFloat(p->sRadius), vec.qw));
        int cpart;
        SOPART **appart;
        func_0025CF18(D_00475480, posMin, posMax, func_001F69F8, 0, &cpart, &appart);
        U normal;
        CMCONTACT acontact[8];
        SOPART *best;
        for (; i < cpart; i++) {
            SOPART *ppart = appart[i];
            if (ppart->grf & (1UL << 17)) {
                qword center = ppart->pxf->pos;
                float g = GFromQw(QwLength(QwSub(center, pos))) - ppart->sRadius - p->sRadius;
                if (g < gDeepest) {
                    vec.qw = QwNormalize(QwSub(pos, ppart->pxf->pos), D_00317530);
                    if (GDot(vel, vec.qw) < 0.0f) {
                        gDeepest = g;
                        normal.qw = vec.qw;
                        best = ppart;
                    }
                }
            } else if (ppart->cplane) {
                int ccontact = func_001CD098(pos, p->sRadius, ppart, (void *)0x7FFFFFFF, 0, 0, 8, acontact);
                for (int j = 0; j < ccontact; j++) {
                    CMCONTACT *pcontact = &acontact[j];
                    float g = GDot(pcontact->pos, pcontact->plane.qw) - pcontact->plane.g[3];
                    if (g < gDeepest && GDot(vel, pcontact->plane.qw) < 0.0f) {
                        normal.qw = pcontact->plane.qw;
                        gDeepest = g;
                        best = ppart;
                    }
                }
            }
        }
        if (gDeepest < 0.0f) {
            qword shift = QwZero();
            for (PSO *o = best->pso; o; o = o->parent) {
                if (o->flags & 0x80) {
                    shift = func_0028BCD0(best->pxf, 0, pos);
                    relVel = QwSub(vel, shift);
                    break;
                }
            }
            qword response;
            {
                U primary;
                register qword relVelVu __asm__("vf4"); /* match the original contact-velocity register */
                if (normal.g[2] > 0.7f && (relVelVu = QwVu(relVel), p->state == 3)) {
                    float gNormal = func_0011FE60(relVelVu, D_00317550, 0, &primary.qw);
                    float gSpeed = GFromQ(QwNormalizeInto(&primary.qw, D_00317560));
                    float gTangent = GMin(p->gTangent.g * gSpeed, 300.0f);
                    gNormal = GMin(-p->gNormalResponse * gNormal, 600.0f);
                    response = QwCombo(VU_FLOAT(gTangent), primary.qw, VU_FLOAT(gNormal), D_00317550);
                    if (!p->hit) {
                        int fTrigger = GDot(response, normal.qw) < p->gThreshold;
                        if (fTrigger) {
                            response = QwCombo(VU_FLOAT(gTangent), primary.qw, VU_FLOAT(p->gBoost.bits), D_00317550);
                            p->hit = best;
                        }
                    }
                } else {
                    U secondary;
                    func_0011FE60(relVel, normal.qw, &primary.qw, &secondary.qw);
                    response = QwCombo(VU_FLOAT(-p->gNormalResponse), primary.qw, VU_FLOAT(p->gTangent.bits), secondary.qw);
                }
            }
            SetPosition(p, QwAddScaled(pos, normal.qw, VU_FLOAT(-gDeepest).qw));
            SetVelocity(p, QwAdd(response, shift));
        }
    }
}

