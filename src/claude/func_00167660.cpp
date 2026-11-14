// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00167660: Sly 3 version of Sly 2 func_0014F110 (src/hand) -- sweep a position toward a target through the
// nearby objects (func_0025CF18 gather + func_001672A0 push-out solve) and step it by the corrected velocity. The
// optional out flag reports a fast move (speed > 100) that was mostly blocked: corrected . requested < 1/4 of the
// requested speed squared.
// Keys: both clock reads go through their own CLOCK pointer (VfDt), so only the high half of &g_clock stays live in
// $s3 across the calls; the float reads of VU values use GetXVu, whose never-selected "j" alternative keeps the value
// a VU-class pseudo (vf1) and leaves the qmfc2 to reload (same helper as src/leaf/func_0020CD88.cpp). No register pins.
typedef int qword __attribute__((mode(TI)));
struct VU_FLOAT { qword q; VU_FLOAT(const float *pg) { __asm__("qmtc2.ni %1, %0" : "=j,j"(q) : "r,V"(*(const int *)pg)); } /* never-chosen "V" (non-offsettable mem) alternative: the word stays a MEM until reload */ };
struct CLOCK { float t, dt, rDt, rDtReal, dtReal; }; /* Sly 2 CLOCK layout */
struct FRAME { int n; FRAME(); ~FRAME(); }; /* out-of-line ctor/dtor: func_001D2770 / func_001D2798(this, 2) */
struct SO;
struct X;
extern "C" {
extern CLOCK g_clock;
extern qword D_00320E10, D_00320E20;
extern float D_0034483C, D_00344844;
extern char D_00475480[];
int func_00167578(void *p, SO *pso);
float func_00167588(void *p, qword a, qword v, X *px);
void func_0025CF18(void *g, qword posMin, qword posMax, int (*pfn)(void *, SO *), void *pv, int *pcso, SO ***papso);
qword func_001672A0(void *p, int cso, SO **apso, int grf, float (*pfn)(void *, qword, qword, X *), qword pos, qword v,
                    float g, float h);
qword func_00167660(void *p, qword pos, qword posTarget, int *pfBlocked);
}
static inline VU_FLOAT VfDt(const CLOCK *pclock) { return VU_FLOAT(&pclock->dtReal); }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Add(qword a, const qword &b) { qword r; __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword DivideBy(const qword &v, const VU_FLOAT &g) { qword r; __asm__("vdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(r) : "j"(v), "j"(g.q)); return r; }
static inline qword AddScaled(qword base, const qword &vec, const VU_FLOAT &s)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(base), "j"(vec), "j"(s.q));
    return r;
}
static inline qword QwDot(const qword &a, const qword &b)
{
    qword d, one;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(a), "j"(b));
    return d;
}
static inline qword QwSqrt(const qword &a) { qword r; __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(r) : "j"(a)); return r; }
/* "r,j": the j alternative only steers the register class of q; "=f,x" can never match a float, so it is never selected */
static inline float GetXVu(qword q) { float g; __asm__("mtc1 %1,%0" : "=f,x"(g) : "r,j"(q)); return g; }

qword func_00167660(void *p, qword pos, qword posTarget, int *pfBlocked)
{
    int cso;
    SO **apso;
    qword v = DivideBy(Sub(posTarget, pos), VfDt(&g_clock));
    qword svSq = QwDot(v, v);
    float sv = GetXVu(QwSqrt(svSq));
    qword posMin = Add(pos, D_00320E10);
    qword posMax = Add(pos, D_00320E20);
    FRAME frame;
    func_0025CF18(D_00475480, posMin, posMax, func_00167578, 0, &cso, &apso);
    qword w = func_001672A0(p, cso, apso, 1, func_00167588, pos, v, D_0034483C, sv + D_00344844);
    if (pfBlocked) {
        *pfBlocked = 0;
        if (sv > 100.0f && GetXVu(QwDot(w, v)) / GetXVu(svSq) < 0.25f)
            *pfBlocked = 1;
    }
    return AddScaled(pos, w, VfDt(&g_clock));
}
