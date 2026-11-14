// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Computes the hit reaction velocity from controller coefficients or the target reaction mode.

typedef unsigned long long qword __attribute__((mode(TI)));
typedef union U { qword q; float f[4]; int bits[4]; } U;
static inline qword VuFloat(float f) { qword q; __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); return q; }
static inline qword VuBitsMem(const int &g) { qword q; __asm__("qmtc2.ni %1, %0" : "=j"(q) : "rV"(g)); return q; }
static inline qword QwSub(qword qw0, qword qw1)
{
    qword qw;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(qw) : "j"(qw0), "j"(qw1));
    return qw;
}
static inline qword QwLength(qword v)
{
    qword qw;
    qword qw2;
    qword vfOne;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(qw), "=j"(vfOne) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(qw2) : "j"(qw));
    return qw2;
}
extern qword D_00317530;
extern qword D_00317550;
static inline float F(qword q) { float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(q)); return g; }
static inline qword DivQ(qword qw, qword v)
{
    qword r;
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(qw), "j"(v));
    return r;
}
static inline qword QwNormalize(qword v)
{
    qword qw = QwLength(v);
    qword fb = D_00317530;
    if (F(qw) < 1.0e-4f)
        return fb;
    return DivQ(qw, v);
}
static inline qword Blend(qword n, qword z, qword a, qword b)
{
    __asm__("vmulax.xyzw $ACC, %1, %2x\n\tvmaddx.xyzw %0, %0, %3x" : "+j"(z) : "j"(n), "j"(a), "j"(b));
    return z;
}
struct VT { short delta, pad; void *fn; };
struct OBJ { char pad0[0xC]; VT *vt; char pad10[0x14 - 0x10]; };
struct MATRIX { qword row[3]; qword pos; };
static inline MATRIX *GetMatrix(OBJ *o) { VT *v = &o->vt[36]; return ((MATRIX *(*)(void *))v->fn)((char *)o + v->delta); }
typedef MATRIX *(*GetMatrixMethod)(void *);
// The scalar temporary is stored after loading the virtual entry and before calling it.
static inline qword ThirdMatrixRow(OBJ *o, U &local, qword value)
{
    VT *v = &o->vt[36];
    GetMatrixMethod method = (GetMatrixMethod)v->fn;
    short delta = v->delta;
    local.q = value;
    return method((char *)o + delta)->row[0];
}

struct CTRL { char pad0[0x3C]; struct CTRLDATA *pdata; };
struct CTRLDATA { char pad0[0x9C]; int unk9C; int sA; int sB; };
struct Q { char pad0[0x14]; OBJ *target; char pad18[8]; int mode; char pad24[0x40 - 0x24]; qword velocity; };
struct P { OBJ *self; char pad4[0x10]; Q *q; };
extern "C" {
int func_0013B500(OBJ *, int);
CTRL *func_002387A8(void *, int);
qword func_001205F0(qword, float);
qword func_001C94E8(OBJ *, OBJ *, qword);
void func_001C21F0(P *, int);
}
struct VEC4 { float x, y, z, w; } __attribute__((aligned(16)));
static const VEC4 kPushA = { 1000.0f, 900.0f, 950.0f, 0.0f };
static const VEC4 kPushB = { 1000.0f, -900.0f, 950.0f, 0.0f };
static inline qword Word(float f) { qword q; __asm__("mfc1 %0, %1" : "=r"(q) : "f"(f)); return q; }
static inline float GetZ(qword q) { float bits; __asm__("prot3w %0, %1" : "=&r"(bits) : "r"(q)); return bits; }
// The repeated scale operand preserves the original VU register allocation.
static inline qword AddScaled(qword base, qword g, qword v) { qword r; __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%3,%2x" : "=j"(r) : "j"(base), "j"(g), "j"(v), "j"(g)); return r; }
static inline qword ScaleX(qword v, qword k) { __asm__("vmulx.xyzw %0, %1, %0x" : "+j"(k) : "j"(v)); return k; }
static inline float Max(float a, float b) { return a > b ? a : b; }
extern "C" void func_001C3008(P *p)
{
    U output;
    U vec, scale;
    OBJ *target;
    CTRL *c;
    if (func_0013B500(p->q->target, 0x3A) && (target = p->q->target, c = func_002387A8((char *)target + 0x29C, 0xD1)) != 0 && c->pdata && c->pdata->unk9C)
    {
        qword selfPos = GetMatrix(p->self)->pos;
        qword tgtPos = GetMatrix(target)->pos;
        vec.q = QwSub(selfPos, tgtPos);
        vec.bits[2] = 0;
        qword n = QwNormalize(vec.q);
        vec.q = n;
        qword axis = D_00317550;
        const CTRLDATA *data = c->pdata;
        const int &bitsB = data->sB;
        const int &bitsA = data->sA;
        qword a = VuBitsMem(bitsA);
        qword b = VuBitsMem(bitsB);
        // Both blend paths end with the same scalar store.
        scale.q = a;
        qword result = Blend(n, axis, a, b);
        output.q = result;
        scale.q = b;
    }
    else
    {
        output.q = p->q->velocity;
        switch (p->q->mode)
        {
        case 0x200:
        case 0x8000:
            if (func_0013B500(p->q->target, 0x32))
            {
                qword k = VuFloat(1.25f);
                vec.q = k;
                qword v = ScaleX(p->q->velocity, k);
                output.q = v;
                output.q = func_001205F0(v, 1200.0f);
                output.f[2] = Max(output.f[2], 700.0f);
            }
            break;
        case 0x40:
            if (func_0013B500(p->q->target, 0x35))
            {
                OBJ *tg = p->q->target;
                qword selfPosition = GetMatrix(p->self)->pos;
                MATRIX *targetMatrix = GetMatrix(tg);
                qword targetPosition = targetMatrix->pos;
                qword neg = Word(-150.0f);
                qword thirdRow = ThirdMatrixRow(tg, vec, neg);
                qword near = AddScaled(targetPosition, neg, thirdRow);
                register qword delta __asm__("vf2"); /* Reuse the original self-position VU register. */
                __asm__("vsub.xyzw %0,%0,%2" : "=j"(delta) : "0"(selfPosition), "j"(near));
                OBJ *origin = 0;
                qword local = func_001C94E8(origin, tg, delta);
                if (GetZ(local) > 0.0f)
                    output.q = func_001C94E8(tg, 0, *(const qword *)&kPushA);
                else
                    output.q = func_001C94E8(tg, 0, *(const qword *)&kPushB);
            }
            break;
        case 0x100:
        default:
            if (func_0013B500(p->q->target, 0x5B))
            {
                vec.q = GetMatrix(p->q->target)->row[0];
            }
            else
            {
                qword otherPosition = GetMatrix(p->self)->pos;
                vec.q = QwSub(otherPosition, GetMatrix(p->q->target)->pos);
            }
            vec.bits[2] = 0;
            qword normalized = QwNormalize(vec.q);
            qword a = VuFloat(600.0f);
            qword b = VuFloat(800.0f);
            qword axis = D_00317550;
            scale.q = a;
            qword result = Blend(normalized, axis, a, b);
            output.q = result;
            vec.q = normalized;
            scale.q = b;
            break;
        }
    }
    OBJ *o = p->self;
    VT *v = &o->vt[40];
    ((void (*)(void *, qword))v->fn)((char *)o + v->delta, output.q);
    func_001C21F0(p, 8);
}
