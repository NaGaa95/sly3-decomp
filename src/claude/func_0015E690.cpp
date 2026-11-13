// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_0015E690: JOBCHASE::Aim (cf. Sly 2 Aim__8JOBCHASE)
typedef int qword __attribute__((mode(TI)));
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
struct VTE { short d; short pad; void *pfn; };
struct M4 { qword r[4]; };
struct G;
struct XEC { char pad[0x20]; qword pos; float g30; };
struct SO { char pad[0xC]; VTE *vt; char pad1[0xD8 - 0x10]; int grfD8; XEC *pxDC; char pad2[0x154 - 0xE0]; SO *pnext; };
struct PSX { char pad[0xA4]; int k; };
struct GEO { int c; qword *av; };
struct PATH { PSX *psx; char pad[0xA0 - 4]; GEO geo; char pad2[0xC0 - 0xA8]; int k; };
struct PSO { char pad[0xC]; VTE *vt; char pad1[0x288 - 0x10]; PATH *ppath; char pad2[0x33C - 0x28C]; int x33C; };
struct LO { char pad[0xC]; VTE *vt; };
struct W { char pad[0x17D0]; LO *plo; };
struct P { char pad[0x10]; W *pw; char pad1[0x48 - 0x14]; float t48; };
struct CLOCK { float t; float dt; };
extern "C" {
extern G D_00475480;
extern SO *D_00479B68;
extern CLOCK D_0036BB98;
extern float D_00320898[2];
PSO *func_001F4AD0(G *pg, int n);
float func_0011E940(float a, float b);
int func_001A9478(G *pg, int n);
int func_0013B500(PSO *p, int n);
void func_0018B1E0(PATH *p);
void func_002541F8(W *pw, void *p);
int func_001E5FF8(SO *p);
int func_0017E208(G *pg, int a, int b, void *c, int d, SO **apso);
int func_0011E8F0(int a, int b);
qword func_0011FDD8(float a, float b, float c);
float func_00120080(qword a, qword b, void *p);
float func_001205C8(qword v);
qword func_0011FD70(float a, float b, float c);
void func_0015E690(P *p);
}
static inline M4 *Mat(void *o) { PSO *s = (PSO *)o; return ((M4 *(*)(void *))s->vt[36].pfn)((char *)s + s->vt[36].d); }
static inline int FLess(float a, float b) { return a < b; }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword SubX(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b), "j"(b)); return r; }
static inline qword Add(qword a, qword b) { qword r; __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline float Len(qword a)
{
    qword d, one; float g;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(d), "=&j"(one) : "j"(a));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
    return g;
}
static inline float LenSq(qword a)
{
    qword d, one; float g;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=&j"(one) : "0"(a));
    __asm__("mtc1 %1, %0" : "=f"(g) : "r"(d));
    return g;
}
static inline float Len2(qword a)
{
    qword d; float g;
    __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=&j"(d) : "j"(a));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
    return g;
}
static inline float GetZ(qword q) { float z; __asm__("pextuw %0, $0, %1" : "=r"(z) : "r"(q)); return z; }
static inline qword AddScaledNorm(qword a, qword v, VU_FLOAT s)
{
    qword d, one, r;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(d), "=&j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(d) : "j"(d), "j"(v));
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(d), "j"(s.q));
    return r;
}

void func_0015E690(P *p)
{
    G *pg = &D_00475480;
    PSO *pso = func_001F4AD0(pg, 0);
    qword posPlayer = Mat(pso)->r[3];
    qword posMe = Mat(p->pw)->r[3];
    qword d = Sub(posPlayer, posMe);
    qword v;
    qword pos;
    register qword q asm("vf4"); /* register pin: the target keeps this value in vf4 */
    {
        VTE *e = &pso->vt[38];
        v = ((qword (*)(void *))e->pfn)((char *)pso + e->d);
    }
    if (100.0f < Len(v))
        p->t48 = D_0036BB98.t;
    float dt = D_0036BB98.t - p->t48;
    if (func_0011E940(D_00320898[0], D_00320898[1]) < dt && !func_001A9478(pg, -1)) {
        if (func_0013B500(pso, 0x33) && pso->x33C == 0x12) {
            pos = Mat(pso)->r[3];
            PATH *ppath = pso->ppath;
            if (ppath->k != ppath->psx->k)
                func_0018B1E0(ppath);
            GEO *pgeo = &ppath->geo;
            for (int i = 0; i < pgeo->c; i++) {
                if (GetZ(pos) < GetZ(pgeo->av[i]))
                    pos = pgeo->av[i];
            }
            goto done;
        }
        func_002541F8(p->pw, pso);
        return;
    }
    for (SO *ps = D_00479B68; ps; ps = ps->pnext) {
        if (!func_001E5FF8(ps)) {
            SO *apso[8];
            qword posT = Mat(ps)->r[3];
            float r = 600.0f;
            if (ps->pxDC) {
                posT = ps->pxDC->pos;
                r = ps->pxDC->g30;
            }
            int c = func_0017E208(&D_00475480, 1, 0x11, ps, 8, apso);
            int k = 0;
            for (int i = 0; i < c; i++) {
                if (apso[i]->grfD8 & 0x200017E)
                    apso[k++] = apso[i];
            }
            if (k) {
                SO *pt = apso[func_0011E8F0(0, k - 1)];
                posT = Mat(pt)->r[3];
                r = *(float *)&pt->pxDC;
            }
            if (600.0f * 600.0f < LenSq(Sub(posT, posPlayer))) continue;
            {
                float pan = func_0011E940(-3.1415927f, 3.1415927f);
                float tilt = func_0011E940(-3.1415927f, 3.1415927f);
                { qword sph = func_0011FDD8(pan, tilt, func_0011E940(0.0f, r)); __asm__("vadd.xyzw %0, %1, %2" : "=j"(q) : "j"(posT), "j"(sph)); }
                qword e = Sub(q, posMe);
                float ld = Len2(d);
                float le = Len2(e);
                __asm__("" : "=j"(q) : "0"(q), "f"(le));
                posT = q;
                if (FLess(le, ld)) {
                    pos = q;
                    goto done;
                }
                float g = func_00120080(d, e, 0);
                if (!(__builtin_fabsf(g) * 57.295776f <= 10.0f)) {
                    pos = posT;
                    goto done;
                }
            }
        }
    }
    if (Len2(v) < 100.0f) {
        qword e = Sub(posMe, posPlayer);
        float rad = func_001205C8(e);
        qword t = func_0011FD70(func_0011E940(rad - 1.5707964f, rad + 1.5707964f), 300.0f, -75.0f);
        __asm__("" : "=r"(t) : "0"(t));
        q = t;
        __asm__("vadd.xyzw %0, %1, %2" : "=j"(pos) : "j"(posPlayer), "j"(q));
    } else {
        pos = AddScaledNorm(posPlayer, v, VU_FLOAT(-300.0f));
    }
done:
    {
        LO *plo = p->pw->plo;
        VTE *e = &plo->vt[34];
        ((void (*)(void *, qword))e->pfn)((char *)plo + e->d, pos);
    }
    func_002541F8(p->pw, p->pw->plo);
}
