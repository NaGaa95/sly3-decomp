// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-regmove -fno-cse-skip-blocks -fno-gcse
// func_001BB228: ballistic intercept of a moving target (Sly 2 relative: func_0019A4A0; called by func_001BBCA8 with the same
// JTAIR/STEPPLAYER views). func_001BB188 solves the vertical intercept time against the target point moving with the velocity
// sampled from the target's space (func_0028BCD0). Without a solution the apex time of the jump is reported and the cost is
// 1010000 minus the height gained by then. Otherwise the hit point is the target point advanced by its velocity for min(t, 0.15),
// the hit velocity is that velocity plus `dpos`, and the cost is half the flight time times the summed XY lengths of the Hermite
// accelerations (func_00118558) at both ends of the arc, clamped to 1000000.
// Allocation notes:
// - The work block reproduces the frame (0x00 hit point, 0x10/0x20 accelerations, 0x30 dead splat store, 0x40 flight time);
//   the sampled velocity, `dpos` and their sum are only read by VU code after calls and land in the spill slots 0x50/0x60/0x70.
// - The solver call and the no-solution path use their own GPR copies of the position (s4) and of the sampled velocity (s0).
// - `vHit` is read back from the sum's spill slot after the hit point is built (lq s0,0x70); -fno-cse-skip-blocks/-fno-gcse keep
//   that copy, -fno-regmove keeps regmove from adding a move for the tied operand of the position-copy asm (it would re-rank the
//   register allocation of the four callee-saved vectors).
typedef int qword __attribute__((mode(TI)));
union VECTOR { qword q; float f[4]; };
struct M4 { VECTOR r[4]; };
struct VTE { short d; short pad; void *fn; };
struct SOPHYS { char pad0[0x80]; VECTOR dvGravity; };
struct LO { char pad0[0xC]; VTE *vt; };
struct STEPPLAYER : LO { char pad10[0xD8 - 0x10]; SOPHYS *psophys; };
struct JTAIR { STEPPLAYER *pstepplayer; };
struct WORK { VECTOR posHit, dvStart, dvEnd, splat; float t; };

extern "C" {
qword func_0028BCD0(void *pspace, void *unused, qword pos);
int func_001BB188(JTAIR *pjtair, qword pos, qword v, qword posTarget, qword vTarget, float *pt);
void func_00118558(float t, float tEval, float scale, qword pos0, qword v0, qword pos1, qword v1, qword *ppos, qword *pv, qword *pdv);
}

static inline qword GetPos(LO *plo) { VTE &v = plo->vt[36]; return ((M4 *(*)(void *))v.fn)((char *)plo + v.d)->r[3].q; }
static inline void *GetSpace(LO *plo, M4 *pmat) { VTE &v = plo->vt[37]; return ((void *(*)(void *, M4 *))v.fn)((char *)plo + v.d, pmat); }
static inline float GMax(float a, float b) { return a > b ? a : b; }
// Z component of a packed GPR vector. A macro so that the pinned register itself is the asm operand: an inline function
// argument would be copied into a fresh pseudo that CSE folds back into the spilled original.
#define GetZ(q) ({ float z_; __asm__("pextuw %0,$0,%1" : "=r"(z_) : "r"(q)); z_; })
static inline qword VuFloat(float g) { qword v; __asm__("qmtc2.ni %1,%0" : "=j"(v) : "r"(g)); return v; }
static inline qword Add(const qword &a, const qword &b) { qword r; __asm__("vadd.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword AddScaled(const qword &base, const qword &vec, const qword &s)
{
    qword r;
    __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(base), "j"(vec), "j"(s));
    return r;
}
static inline float LengthXY(qword v)
{
    qword d;
    float f;
    __asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y" : "=j"(d) : "j"(v));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(v) : "j"(d));
    __asm__("mtc1 %1,%0" : "=f"(f) : "r"(v));
    return f;
}

extern "C" void func_001BB228(JTAIR *pjtair, qword vLaunch, LO *plo, qword posTarget, qword dpos,
                              float *pt, float *pg, qword *pposHit, qword *pvHit)
{
    WORK w;
    qword pos = GetPos(pjtair->pstepplayer);
    qword posSolve = pos;
    __asm__("" : "+r"(posSolve)); // empty asm: own copy of the position for the solver call and the no-solution path
    qword vTarget = func_0028BCD0(GetSpace(plo, 0), 0, posTarget);
    register qword vSolve asm("$16") = vTarget; // register pin: GPR copy of the sampled velocity (the original stays spilled)

    if (!func_001BB188(pjtair, posSolve, vLaunch, posTarget, vSolve, &w.t)) {
        float dz = GetZ(vLaunch) - GetZ(vSolve);
        float g = pjtair->pstepplayer->psophys->dvGravity.f[2];
        float t = GMax(0.0f, -dz / g);
        float tHalf = t * 0.5f;
        float h = GetZ(posSolve);
        h -= GetZ(posTarget);
        h += g * tHalf * t + dz * t;
        if (pt) *pt = t;
        if (pg) *pg = 1010000.0f - h;
        return;
    }
    {
        float t = w.t;
        float tLimit = 0.15f;
        float tLead = t < tLimit ? t : tLimit;
        qword vSum = Add(vTarget, dpos);
        w.splat.q = VuFloat(tLead);
        w.posHit.q = AddScaled(posTarget, vTarget, w.splat.q);
        qword vHit = vSum;
        if (pt) *pt = t;
        if (pg) {
            float g;
            func_00118558(w.t, 0.0f, 1.0f, pos, vLaunch, w.posHit.q, vSum, 0, 0, &w.dvStart.q);
            g = LengthXY(w.dvStart.q);
            func_00118558(w.t, w.t, 1.0f, pos, vLaunch, w.posHit.q, vSum, 0, 0, &w.dvEnd.q);
            g += LengthXY(w.dvEnd.q);
            float tMid = w.t * 0.5f;
            g *= tMid;
            *pg = g < 1000000.0f ? g : 1000000.0f;
        }
        if (pposHit) *pposHit = w.posHit.q;
        if (pvHit) *pvHit = vHit;
    }
}
