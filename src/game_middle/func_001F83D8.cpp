// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Find a landing point on the objects around `point`: casts a line from point up to point + axis * gMax and, failing
// that, from just above point down to point + axis * gMin, against the candidate list `apcand` (when the caller passed
// none, the candidates along the whole range point + axis * [gMin, gMax] are gathered first). Returns 1 and the hit
// position, or 1 and point itself when gMin >= 0 and nothing above was found. Based on Sly 2 func_001C6DE8.
typedef int qword __attribute__((mode(TI)));
union VECTOR4 { qword q; float f[4]; };
struct LSG {
    VECTOR4 posA;           // 0x00: hit point (lower cast)
    VECTOR4 posB;           // 0x10: hit point (upper cast)
    VECTOR4 normalA;        // 0x20
    VECTOR4 normalB;        // 0x30
    float t;                // 0x40
    float u;                // 0x44
    char pad48[0x18];
};
struct FRAME { int n; FRAME(); ~FRAME(); };   // out-of-line ctor/dtor 0x1D2770 / 0x1D2798
struct CANDIDATE;
struct VU_FLOAT {
    qword q;
    VU_FLOAT(float f) { __asm__("qmtc2.ni %1,%0" : "=j"(q) : "r"(f)); }
};
struct VV { qword q; VV() {} VV(const qword &v) { q = v; } operator qword() const { return q; } };
extern "C" {
int func_001F69F8(void *, CANDIDATE *);
void func_0025CF18(void *, qword, qword, int (*)(void *, CANDIDATE *), void *, int *, CANDIDATE ***);
int func_00165000(int, qword, qword, int, CANDIDATE **, LSG *);
extern char D_00475480[];
extern qword D_00317550;
}
// base + v * g
static inline qword AddScaled(VV base, qword v, VU_FLOAT g)
{
    qword r;
    __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(base.q), "j"(v), "j"(g.q));
    return r;
}

extern "C" int func_001F83D8(float gMin, float gMax, float gThreshold, qword point, int ccand, CANDIDATE **apcand,
                             qword *ppos)
{
    LSG lsg;
    FRAME frame;
    VV posMax, posMin;
    posMax = AddScaled(point, D_00317550, VU_FLOAT(gMax));
    posMin = AddScaled(point, D_00317550, VU_FLOAT(gMin));
    if (!apcand)
        func_0025CF18(D_00475480, posMin.q, posMax.q, func_001F69F8, 0, &ccand, &apcand);
    if (gMax > 0) {
        if (func_00165000(0, point, posMax, ccand, apcand, &lsg) && lsg.t == 0) {
            if (lsg.u == 1 || lsg.normalB.f[2] < gThreshold)
                return 0;
            *ppos = lsg.posB.q;
            return 1;
        }
    }
    if (gMin < 0) {
        qword start = AddScaled(point, D_00317550, VU_FLOAT(1.0f));
        if (func_00165000(0, start, posMin, ccand, apcand, &lsg)) {
            if (lsg.t == 0 || lsg.normalA.f[2] < gThreshold)
                return 0;
            *ppos = lsg.posA.q;
            return 1;
        }
        return 0;
    }
    *ppos = point;
    return 1;
}
