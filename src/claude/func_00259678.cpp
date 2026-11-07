// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00259678: steer a four-way locomotion blend (cf. Sly 2 func_0020CAC8): at a foot-down moment pick the
// leg animation whose root velocity best matches the wanted direction (the current one favoured by 1.1),
// switch to it at the same phase, then set the velocity to direction * that animation's speed.
typedef int qword __attribute__((mode(TI)));
struct VU_FLOAT { qword qw; };
struct ASEG { char pad[0x64]; float tMax; };
struct ASEGA { char pad[0x14]; ASEG *paseg; };
struct E
{
    ASEG *paseg;
    int pad[3];
    qword v;
    float s;
    float ag24[2];
    char pad2C0[0];
    float ag2C[2];
    char pad34[0xC];
};
struct P
{
    char pad0[0x10];
    qword v;
    void *palo;
    ASEGA *pasega;
    E *ae;
    E *peCur;
    int grf;
};
extern "C" {
extern char D_00341FF0[];
float func_00259638(P *p, float *pg);
int func_0011EE30(void *p, float g);
void func_00137588(ASEG *paseg, void *palo, float t, float svt, int grf, ASEGA **ppasega);
}
static inline qword QwNormalize(qword v)
{
    qword d, one, r;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(d), "=&j"(one) : "j"(v), "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "0"(d));
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(d), "j"(v));
    return r;
}
static inline float GDot(qword a, qword b)
{
    qword one;
    float g;
    __asm__("vmul.xyz %0, %2, %0\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(b), "=&j"(one) : "j"(a), "0"(b));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(b));
    return g;
}
static inline qword QwScale(qword v, VU_FLOAT g)
{
    qword r;
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(v), "j"(g.qw));
    return r;
}

extern "C" void func_00259678(P *p, qword v)
{
    qword dir = QwNormalize(v);
    E *peBest = 0;
    float gMax = -3.40282347e+38f;
    float g0 = func_00259638(p, p->peCur->ag24);
    float g1 = func_00259638(p, p->peCur->ag2C);
    int f0 = func_0011EE30(D_00341FF0, g0);
    int f1 = func_0011EE30(D_00341FF0, g1);
    if (f0 || f1)
    {
        for (unsigned int i = 0; i < 4; i++)
        {
            E *pe = &p->ae[i];
            ASEG *paseg = pe->paseg;
            if (!paseg)
                continue;
            float g = GDot(dir, QwNormalize(pe->v));
            if (paseg == p->pasega->paseg)
                g *= 1.1f;
            if (gMax < g)
            {
                gMax = g;
                peBest = pe;
            }
        }
        if (peBest != p->peCur)
        {
            float gPhase;
            float *pg;
            if (f0)
            {
                gPhase = g0;
                pg = peBest->ag24;
            }
            else
            {
                gPhase = g1;
                pg = peBest->ag2C;
            }
            float t = pg[0] + gPhase * pg[1];
            if (peBest->paseg->tMax < t)
                t -= peBest->paseg->tMax;
            func_00137588(peBest->paseg, p->palo, t, 1.0f, p->grf, &p->pasega);
            p->peCur = peBest;
        }
    }
    VU_FLOAT vuS;
    __asm__("qmtc2 %1, %0" : "=j"(vuS.qw) : "rV"(*(int *)&p->peCur->s));
    p->v = QwScale(dir, vuS);
}
