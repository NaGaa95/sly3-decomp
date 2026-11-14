// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Update motion around the target anchor, then apply the response to the linked object if present.
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; int i[4]; };
struct M3 { U r[3]; };
struct M4 { U r[4]; };
struct BASE { int x0, x4, x8; };
struct ACCEL { char pad0[0x80]; U value; };
struct VTE { short delta, pad; void *fn; };
struct OBJ : BASE { VTE *vt; };
struct NODE : OBJ { char pad10[0x148]; float property; };
struct LINK { int header; NODE *object; };
struct DELTA { U first, second; };
struct P : OBJ {
    char pad10[0xC8];
    ACCEL *accel;
    char padDC[0x19E8 - 0xDC];
    int state;
    float stamp;
    char pad19F0[4];
    NODE *target;
    char pad19F8[0x1A00 - 0x19F8];
    int reverse;
    LINK *other;
    char pad1A08[8];
    DELTA response[2];
};
struct CLQ { float g0, g1, g2; };
struct LM { float gMin, gMax; };
struct SMPA { float a, b, duration, limit; };
struct CLOCK { float t, dt; };
struct STATE { U direction, position, velocity; M3 rotation; };
struct VU_FLOAT { qword qw; };
extern "C" {
qword func_0028BCD0(void*,void*,qword);
float func_0011FE60(qword,qword,qword*,qword*);
float func_0011E730(float,float,float,float,SMPA*,float*);
M3 func_0011C930(qword);
void func_001B0CC0(P*,NODE*,qword*,qword*,DELTA*);
extern U D_00317560,D_00317530,D_00317540,D_00317550;
extern CLQ D_00322B50,D_00322B70;
extern LM D_00322B60,D_00341FF0;
extern SMPA D_00322B80;
extern CLOCK D_0036BB98;
}
static inline M4*GetMatrixOf(OBJ*p){VTE&v=p->vt[36];return((M4*(*)(void*))v.fn)((char*)p+v.delta);}
static inline void*GetSpaceOf(OBJ*p){VTE&v=p->vt[37];return((void*(*)(void*,int))v.fn)((char*)p+v.delta,0);}
static inline qword GetVelocityOf(OBJ*p){VTE&v=p->vt[38];return((qword(*)(void*))v.fn)((char*)p+v.delta);}
static inline int FloatBits(float f){union{float f;int i;}u;u.f=f;return u.i;}
static inline VU_FLOAT VuFloatInt(int n){VU_FLOAT v;__asm__("qmtc2.ni %1,%0":"=j"(v.qw):"r"(n));return v;}
static inline VU_FLOAT VuFloat(float g){VU_FLOAT v;__asm__("qmtc2.ni %1,%0":"=j"(v.qw):"r"(g));return v;}
static inline VU_FLOAT VuFloatFromMemWord(int n){VU_FLOAT v;__asm__("qmtc2.ni %1,%0":"=j"(v.qw):"rV"(n));return v;}
static inline qword QwAdd(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword QwSub(const qword&a,const qword&b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword QwScaleX(qword a,VU_FLOAT g){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(g.qw));return r;}
static inline qword QwAddScaled(qword base,qword vec,VU_FLOAT k){qword r;__asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(base),"j"(vec),"j"(k.qw));return r;}
static inline qword QwDot(qword a,qword b){qword r,one;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(r),"=j"(one):"j"(a),"j"(b));return r;}
static inline qword QwSqrt(qword a){qword r;__asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"=j"(r):"j"(a));return r;}
static inline qword QwDivide(const qword&a,const qword&g){qword r;__asm__("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q":"=j"(r):"j"(a),"j"(g));return r;}
static inline qword QwDivideBy(const qword&a,const qword&g){qword r;__asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q":"=j"(r):"j"(g),"j"(a));return r;}
static inline float GXOfQw(qword qw){float x;__asm__("mtc1 %1,%0":"=f"(x):"r"(qw));return x;}
static inline qword QwCross(qword a,qword b){qword r;__asm__("vopmula.xyz $ACC,%1,%2\n\tvopmsub.xyz %0,%2,%1":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword QwRotateVec(const M3*m,qword v){qword r;__asm__("vmulax.xyz $ACC,%2,%1x\n\tvmadday.xyz $ACC,%3,%1y\n\tvmaddz.xyz %0,%4,%1z":"=j"(r):"j"(v),"j"(m->r[0].q),"j"(m->r[1].q),"j"(m->r[2].q));return r;}
static inline qword QwCombo(const qword&a,const qword&b,VU_FLOAT ka,VU_FLOAT kb){qword r;__asm__("vmulax.xyzw $ACC,%3,%1x\n\tvmaddx.xyzw %0,%4,%2x":"=j"(r):"j"(ka.qw),"j"(kb.qw),"j"(a),"j"(b));return r;}
static inline qword QwScaleXK(qword a,VU_FLOAT g){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(g.qw),"j"(g.qw));return r;}
static inline qword QwProjectOut(const qword&v,const qword&axis){VU_FLOAT d;d.qw=QwDot(v,axis);return QwSub(v,QwScaleX(axis,d));}
static inline float GXOfVf(qword qw){float x;__asm__("mtc1 %1,%0":"=f"(x):"r"(qw),"j"(qw));return x;}
static inline qword NormalizeAt(U*pv,const U*pfallback){qword len=QwSqrt(QwDot(pv->q,pv->q));if(GXOfVf(len)<0.0001f)*pv=*pfallback;else pv->q=QwDivide(pv->q,len);return len;}
static inline float GLength(qword v){return GXOfQw(QwSqrt(QwDot(v,v)));}
static inline float GEvaluateClq(CLQ*p,float x){return p->g0+x*(p->g1+x*p->g2);}
static inline float GLimitG(float g,float gMin,float gMax){if(g<gMin)return gMin;if(gMax<g)return gMax;return g;}
static inline float GMinOf(float a,float b){return(b<a)?b:a;}
static inline float GMaxOf(float a,float b){return(b>a)?b:a;}
static inline qword QwNormalize(qword v,qword fallback){qword len=QwSqrt(QwDot(v,v));qword r;if(GXOfQw(len)<0.0001f)r=fallback;else r=QwDivide(v,len);return r;}
static inline CLOCK*Addr(CLOCK*p){return p;}
static inline qword QwAddScaled2Q(qword base,qword a,qword b,qword k){qword r;__asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddax.xyzw $ACC,%2,%4x\n\tvmaddx.xyzw %0,%3,%4x":"=j"(r):"j"(base),"j"(a),"j"(b),"j"(k),"j"(k));return r;}
extern "C" void func_001B0FF0(P *p)
{
    U anchor, displacement, anchorVelocity, axis;
    anchor.q = GetMatrixOf(p->target)->r[3].q;
    qword row1 = GetMatrixOf(p->target)->r[1].q;
    qword up = QwDivide(row1, QwSqrt(QwDot(row1, row1)));
    anchorVelocity.q = func_0028BCD0(GetSpaceOf(p->target), 0, anchor.q);
    axis.q = QwSub(GetMatrixOf(p)->r[3].q, anchor.q);
    displacement = axis;
    qword length = NormalizeAt(&axis, &D_00317550);
    float distance = GXOfVf(length);

    U relative, perpendicular, parallel;
    relative.q = QwSub(GetVelocityOf(p), anchorVelocity.q);
    float radial = func_0011FE60(relative.q, axis.q, &parallel.q, &perpendicular.q);
    U firstAxis, angularFirst;
    firstAxis.q = QwNormalize(QwCross(axis.q, perpendicular.q), D_00317530.q);
    float ratio = GLength(perpendicular.q) / distance;
    angularFirst.q = QwScaleX(firstAxis.q, VuFloat(ratio));
    U projected;
    projected.q = QwProjectOut(p->accel->value.q, axis.q);
    U secondAxis, angularSecond;
    secondAxis.q = QwNormalize(QwCross(axis.q, projected.q), D_00317540.q);
    angularSecond.q = QwScaleX(secondAxis.q, VuFloat(GLength(projected.q) / distance));

    float drag = GLimitG(GEvaluateClq(&D_00322B50, ratio), D_00322B60.gMin, D_00322B60.gMax);
    float bias;
    if (p->state == 0 || p->state == 2)
        bias = -2.5f;
    else
        bias = -1.0f;
    U angular, parallelAngular, perpendicularAngular;
    angular.q = QwAddScaled(angularFirst.q, angularSecond.q, VuFloatFromMemWord(*(int *)&Addr(&D_0036BB98)->dt));
    func_0011FE60(angular.q, up, &parallelAngular.q, &perpendicularAngular.q);
    angular.q = QwCombo(parallelAngular.q, perpendicularAngular.q,
                       VuFloat(drag * Addr(&D_0036BB98)->dt + 1.0f),
                       VuFloat(bias * Addr(&D_0036BB98)->dt + 1.0f));
    if ((p->state == 0 || p->state == 2) && D_0036BB98.t - p->stamp < 0.25f) {
        float amount = Addr(&D_0036BB98)->dt * 5.0f;
        if (p->state == 0)
            amount = -amount;
        if (p->reverse)
            amount = -amount;
        float speed = GLength(perpendicular.q);
        float down = -p->accel->value.f[2];
        float t = (down * displacement.f[2] + speed * 0.5f * speed) / down;
        float g = D_00322B70.g0;
        g += t * (D_00322B70.g1 + t * D_00322B70.g2);
        float lo = D_00341FF0.gMin, hi = D_00341FF0.gMax;
        if (g < lo)
            g = lo;
        else if (hi < g)
            g = hi;
        amount *= g;
        angular.q = QwAddScaled(angular.q, up, VuFloat(amount));
    }
    float speedOut;
    float next = func_0011E730(distance, radial, 230.0f - p->target->property,
                             Addr(&D_0036BB98)->dt, &D_00322B80, &speedOut);
    angular.q = QwScaleX(angular.q, VuFloatInt(FloatBits(GMinOf(230.0f, distance) / GMaxOf(75.0f, next))));

    U velocity;
    STATE state;
    if (p->other) {
        NODE *object = p->other->object;
        qword base;
        qword dt;
        // Reload the timestep bits into a0 so v0 remains available for the zero-vector address and anchor velocity.
        __asm__ __volatile__("" : "=r"(dt) : "0V"(*(int *)&D_0036BB98.dt) : "$2");
        typedef M4 *(*MatrixMethod)(void *);
        state.direction = D_00317560;
        qword point = anchor.q, spin = D_00317560.q;
        {
            // Keep the anchor-velocity reload in the original v0 so it does not displace the timestep in a0.
            register qword v asm("$2");
            asm volatile("" : "=r"(v) : "0V"(anchorVelocity.q));
            base = v;
        }
        state.position = D_00317560;
        VTE &mv = object->vt[36];
        state.velocity.q = dt;
        MatrixMethod getMatrix = (MatrixMethod)mv.fn;
        short adjustment = mv.delta;
        qword arm = QwSub(point, getMatrix((char *)object + adjustment)->r[3].q);
        velocity.q = QwAddScaled2Q(base, spin, QwCross(spin, arm), dt);
    } else
        velocity = anchorVelocity;

    state.rotation = func_0011C930(QwScaleX(QwAdd(angularFirst.q, angular.q), VuFloat(Addr(&D_0036BB98)->dt * 0.5f)));
    state.direction.q = QwRotateVec(&state.rotation, axis.q);
    qword radius = QwScaleXK(state.direction.q, VuFloat(next));
    state.position.q = QwAdd(anchor.q, radius);
    qword final = QwAdd(QwAdd(velocity.q, QwCross(angular.q, radius)),
                       QwScaleX(state.direction.q, VuFloatFromMemWord(*(int *)&speedOut)));
    state.velocity.q = final;
    qword current = GetVelocityOf(p);
    projected.q = QwSub(QwDivideBy(QwSub(final, current), VuFloatFromMemWord(*(int *)&Addr(&D_0036BB98)->dt).qw),
                        p->accel->value.q);
    if (p->other)
        func_001B0CC0(p, p->other->object, &anchor.q, &projected.q, p->response);
    else
        p->response[0].first = projected;
}
