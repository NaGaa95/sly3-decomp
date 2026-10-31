// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct VF { qword q; VF(float f) { __asm__("mfc1 %0, %1" : "=r"(q) : "f"(f)); } };
struct VU_VECTOR { qword q; VU_VECTOR(const qword &v) { q = v; } };
struct VEntry { short delta; short pad; void *(*get)(void *); };
struct LO { char pad[0xC]; VEntry *table; };
struct ST { LO *plo; void *pv; };
struct CTX { int a; CTX(); ~CTX(); };
extern "C" {
extern char D_00475480[];
LO *func_001F4A80(void *p);
int func_00167F60(LO *p, qword v, VF w);
int func_0025CEC8(void *pctx, void *p);
void func_0025CF18(void *game, qword a, qword b, int (*pfn)(void *, void *), void *pctx, int *pc, void ***pap);
void *func_00165000(int grf, qword a, qword b, int n, void **ap, void *phit);
}
#define XFP(o) ((qword *)(o)->table[36].get((char *)(o) + (o)->table[36].delta))
static inline float Dist(qword a, qword b)
{
    qword d, one;
    float g;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(d));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
    return g;
}
static inline qword Normalize(qword v)
{
    qword d, one, r;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(d), "j"(v));
    return r;
}
static inline qword NormalizeP(qword v)
{
    register qword d asm("vf3"); /* register pin: length temp in vf3 like the target */
    qword one, r;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(d), "j"(v));
    return r;
}
static inline qword Sub(qword a, qword b) { qword d; __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
static inline qword Add(qword a, qword b) { qword d; __asm__("vadd.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
static inline qword Scale(qword a, VF s) { qword d; __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(d) : "j"(a), "j"(s.q)); return d; }
static inline qword Cross(qword a, qword b) { qword d; __asm__("vopmula.xyz $ACC, %1, %2\n\tvopmsub.xyz %0, %2, %1" : "=j"(d) : "j"(a), "j"(b)); return d; }
extern "C" int func_00161DF8(ST *p, float r, float gMax)
{
    qword pos = XFP(p->plo)[3];
    VU_VECTOR vSrc(pos);
    LO *plo = func_001F4A80(p->pv);
    qword posDst = XFP(plo)[3];
    if (!func_00167F60(plo, pos, VF(r)))
        return 0;
    int fFar = gMax < Dist(pos, posDst);
    if (fFar)
        return 0;
    CTX ctx;
    int cHit = 0;
    int c;
    void **ap;
    func_0025CF18(D_00475480, vSrc.q, posDst, func_0025CEC8, 0, &c, &ap);
    qword apos[4];
    qword up = XFP(plo)[1];
    qword dir = NormalizeP(Sub(posDst, vSrc.q));
    qword vUp = Scale(up, VF(r));
    qword side = Cross(up, dir);
    qword vDir = Scale(dir, VF(r));
    side = Normalize(side);
    qword vc = Add(vSrc.q, vDir);
    apos[1] = Add(vc, vUp);
    apos[2] = Sub(vc, vUp);
    apos[3] = Add(vc, Scale(side, VF(r)));
    apos[0] = vc;
    qword *pp = apos;
    for (unsigned int i = 0; i < 4; i++, pp++) {
        if (func_00165000(0, posDst, *pp, c, ap, 0))
            cHit++;
    }
    if (cHit == 4)
        return 0;
    return 1;
}
