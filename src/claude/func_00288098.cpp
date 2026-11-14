// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00288098: follow the target position - query the placement (func_00287890), refresh the
// tracked value and actuator, and when it moved more than 1 unit turn the XF frame by the rotation from its x axis to
// the (safe-normalised) move and shift its position. Matching notes: `out` is a float[4] struct (BLKmode, slot 0);
// mat = r * mat with r assigned (3-store pattern); DotQ carries two allocation-only "j"(v) operands; no pins.
typedef int qword __attribute__((mode(TI)));
struct M3 { qword r[3]; };
struct VU_VECTOR4 { qword qw; };
inline M3 operator*(const M3 &matL, const M3 &matR) return mat
{
    qword qwL0 = matL.r[0];
    qword qwL1 = matL.r[1];
    qword qwL2 = matL.r[2];
    VU_VECTOR4 v0;
    VU_VECTOR4 v1;
    VU_VECTOR4 v2;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(v0.qw) : "j"(qwL0), "j"(qwL1), "j"(qwL2), "j"(((VU_VECTOR4 *)&matR.r[0])->qw));
    *(VU_VECTOR4 *)&mat.r[0] = v0;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(v1.qw) : "j"(qwL0), "j"(qwL1), "j"(qwL2), "j"(((VU_VECTOR4 *)&matR.r[1])->qw));
    *(VU_VECTOR4 *)&mat.r[1] = v1;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(v2.qw) : "j"(qwL0), "j"(qwL1), "j"(qwL2), "j"(((VU_VECTOR4 *)&matR.r[2])->qw));
    *(VU_VECTOR4 *)&mat.r[2] = v2;
}
struct XF { M3 mat; qword pos; };
struct BONE { char pad[0x70]; qword pos; };
struct VTE { short d; short pad; void *(*pf)(void *, ...); };
struct Q { char pad[0x18]; int x18; };
struct ITEM { BONE *bone; char pad[0xCC]; };
struct O {
    char pad[0xC]; VTE *vt; char pad10[0xD0 - 0x10]; int count; ITEM *aitem; char padD8[0x130 - 0xD8];
    Q *x130; char pad134[4]; void *x138; char pad13C[0x150 - 0x13C]; qword q150; void *x160; void *x164;
};
extern "C" {
extern qword D_00317530, D_00317560;
int func_00287890(void *, qword, qword *);
void func_00287F48(O *);
qword func_0028E910(int, void *, qword);
void func_0023D938(O *, qword);
void func_0023D9D0(O *, qword);
M3 func_0011CDC8(qword, qword);
void func_0023EBF8(O *, int);
void func_0023EC98(O *, int);
void func_0023B978(O *, void *);
}
static inline XF *Xf(O *o) { VTE *v = &o->vt[36]; return (XF *)v->pf((char *)o + v->d); }
static inline qword Sub(const qword &a, const qword &b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Add(qword a, const qword &b) { qword r; __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword DotQ(qword v)
{
    qword d, one;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(d), "=&j"(one) : "j"(v), "j"(v), "j"(v));
    return d;
}
static inline float GetX(qword q) { float f; int t; __asm__("qmfc2.ni %1, %2\n\tmtc1 %1, %0" : "=f"(f), "=&r"(t) : "j"(q)); return f; }
static inline qword SqrtQ(qword d) { qword l; __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d)); return l; }
static inline qword DivQ(qword v, qword l)
{
    qword r;
    __asm__ __volatile__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(l), "j"(v));
    return r;
}
static inline void SafeNormalize(qword *pv, qword l, qword v, qword def)
{
    if (GetX(l) < 0.0001f)
        *pv = def;
    else
        *pv = DivQ(v, l);
}
extern "C" void func_00288098(O *p)
{
    struct { float f[4]; } __attribute__((aligned(16))) out;
    if (!p->x130)
        return;
    qword pos = p->aitem[0].bone->pos;
    if (!func_00287890(p->x164, pos, (qword *)&out)) {
        func_00287F48(p);
        return;
    }
    p->q150 = func_0028E910(0, p->x138, *(qword *)&out);
    Q *pq;
    void *pv;
    if (p->x130->x18 == 1) {
        pq = 0;
        pv = 0;
    } else {
        pq = p->x130;
        pv = p->x138;
    }
    p->vt[10].pf((char *)p + p->vt[10].d, pq, pv, 0x13);
    func_0023D938(p, D_00317560);
    func_0023D9D0(p, D_00317560);
    qword d = Sub(pos, *(qword *)&out);
    qword dd = DotQ(d);
    if (1.0f < GetX(dd)) {
        qword dir;
        SafeNormalize(&dir, SqrtQ(dd), d, D_00317530);
        M3 mat = Xf(p)->mat;
        M3 r;
        r = func_0011CDC8(mat.r[0], dir);
        mat = r * mat;
        p->vt[35].pf((char *)p + p->vt[35].d, &mat);
        VTE *e = &p->vt[34];
        qword d2 = Sub(pos, p->aitem[0].bone->pos);
        e->pf((char *)p + e->d, Add(Xf(p)->pos, d2));
    }
    func_0023EBF8(p, 1);
    func_0023EC98(p, 1);
    for (int i = 0; i < p->count; i++)
        func_0023B978(p, &p->aitem[i]);
}
