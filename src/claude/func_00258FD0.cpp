// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00258FD0 (agents A71/A73): one-time setup of a jump arc from three markers (oids 0x3D-0x3F) and the animation curve
// (cf. Sly 2 func_0020C5C8): times, horizontal distance and the curve's vertical acceleration.
// The distance is stored with an A65-style lane-store helper (gcc emits the qmfc2 itself); the vsqrt asm is split from
// the vmul/vaddy asm so the qmfc2 issues after the sub.s as in the target.
typedef int qword __attribute__((mode(TI)));
struct VECTOR4 { float x, y, z, w; } __attribute__((aligned(16)));
struct XF;
struct KEY
{
    virtual void Load(void *pbis);
};
struct VECKEY : public KEY
{
    virtual void CacheSeg(XF *pxf);
    virtual void GetValue(float t, float svt, qword *ppos, qword *pv);
};
struct CHN { int n0; VECKEY *pkey; };
struct MARKER { float t; };
struct P
{
    char pad0[0x40];
    void *paseg;
    float tA, tB, tC, dtCA, dtCB;
    float sDist;
    char pad5C[4];
    float vx, vy, vz;
    char pad6C[0x84 - 0x6C];
    int fInit;
};
extern "C" {
extern char D_00475480[];
MARKER *func_00136880(void *paseg, int oid);
void *func_0017E5D8(void *psw, int a, int b, P *p);
CHN *func_00136EE0(void *paseg, void *palo, int xfk, int fStripped);
}
static inline qword DistXYq(qword a, qword b)
{
    qword d;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xy %0, %0, %0\n\tvaddy.x %0, %0, %0y" : "=j"(d) : "0"(d));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "0"(d));
    return d;
}
static inline void StoreX(float *dst, qword q) { __asm__("sw %1, %0" : "=m"(*dst) : "r"(q)); }
extern "C" void func_00258FD0(P *p)
{
    MARKER *pa, *pb, *pc;
    CHN *pchn;
    VECTOR4 v0, v1, v2;
    float t, h;
    if (!p->paseg || p->fInit)
        return;
    p->fInit = 1;
    pa = func_00136880(p->paseg, 0x3D);
    if (!pa)
        return;
    pb = func_00136880(p->paseg, 0x3E);
    if (!pb)
        return;
    pc = func_00136880(p->paseg, 0x3F);
    if (!pc)
        return;
    p->tA = pa->t;
    p->tB = pb->t;
    p->tC = pc->t;
    p->dtCB = p->tC - p->tB;
    p->dtCA = p->tC - p->tA;
    pchn = func_00136EE0(p->paseg, func_0017E5D8(D_00475480, 3, 0x32, p), 1, 1);
    pchn->pkey->GetValue(p->tA, 1.0f, (qword *)&v0, 0);
    pchn->pkey->GetValue(p->tC, 1.0f, (qword *)&v1, 0);
    t = p->tA;
    h = (p->tC - t) * 0.5f;
    { float th = t + h;
    StoreX(&p->sDist, DistXYq(*(qword *)&v0, *(qword *)&v1));
    pchn->pkey->GetValue(th, 1.0f, (qword *)&v2, 0); }
    {
        float *pv = &p->vx;
        pv[0] = 0;
        pv[1] = 0;
        pv[2] = (-v2.z + v0.z) / (h * h * 0.5f);
    }
}
