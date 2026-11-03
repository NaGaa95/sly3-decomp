// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Blend the frame `out` towards the frame `source` (rotation rows 0..2, position row 3) by the fraction step/time:
// the relative rotation is decomposed to angle/axis and scaled by the fraction, the remaining rotation error
// (source * inverse(out), after orthonormalising both) is blended with the identity, and the position/velocity
// pair goes through the Hermite helper func_00118558.  The result frame is written to `state`.
// Layout notes: a/p/b/q are declared first (stack order), m and s are reused for several values, `pos` is
// declared right before the Hermite call; the helper by-value temporaries (VF, NRV matrices) give the original frame.
// The Hermite prototype lists the floats first (private spelling; it only affects the argument set-up order).
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; int i[4]; };
struct M3 { U r[3]; };
struct M4 { U r[4]; };
struct VECTOR { float x, y, z, w; };
extern "C" {
extern M3 D_00317490;
void func_0011C798(M3 *);
M3 func_0011C6F8(const M3 *);
M3 func_0011CFC0(M3 *, M3 *);
void func_0011D0B8(M3 *, float *, qword *);
M3 func_0011C8C0(float, qword);
void func_00118558(float, float, float, qword, qword, qword, qword, qword *, qword *, qword *);
void *func_00291E8C(void *, const void *, int);
qword *func_002BA818(VECTOR *, qword);
}
static inline M3 Mul(const M3 &a, const M3 &b) return r
{
    qword a0 = a.r[0].q, a1 = a.r[1].q, a2 = a.r[2].q;
    __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z" : "=j"(r.r[0].q) : "j"(a0), "j"(a1), "j"(a2), "j"(b.r[0].q));
    __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z" : "=j"(r.r[1].q) : "j"(a0), "j"(a1), "j"(a2), "j"(b.r[1].q));
    __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z" : "=j"(r.r[2].q) : "j"(a0), "j"(a1), "j"(a2), "j"(b.r[2].q));
}
struct VF { qword q; VF(float g) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(g)); } };
static inline qword MulX(qword a, VF s) { qword r; __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(a), "j"(s.q)); return r; }
static inline M3 Scaled(const M3 &m, VF u) return ret
{
    M3 r;
    r.r[0].q = MulX(m.r[0].q, u);
    r.r[1].q = MulX(m.r[1].q, u);
    r.r[2].q = MulX(m.r[2].q, u);
    func_00291E8C(&ret, &r, sizeof(M3));
}
static inline qword Add(qword a, qword b) { qword r; __asm__("vadd.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline M3 Plus(const M3 &a, const M3 &b) return r
{
    for (int i = 0; i < 3; i++)
        r.r[i].q = Add(a.r[i].q, b.r[i].q);
}
extern "C" void func_001F2408(M4 *out, M4 *source, qword start, qword end, M4 *state, qword *anchor, float time, float step)
{
    float t = step / time;
    M3 a, p, b, q;
    a = *(M3 *)out;
    func_0011C798(&a);
    p = Mul(func_0011C6F8(&a), *(M3 *)out);
    b = *(M3 *)source;
    func_0011C798(&b);
    q = Mul(func_0011C6F8(&b), *(M3 *)source);
    M3 m, s;
    U axis;
    float rad;
    m = func_0011CFC0(&a, &b);
    func_0011D0B8(&m, &rad, &axis.q);
    m = func_0011C8C0(t * rad, axis.q);
    s = Mul(q, func_0011C6F8(&p));
    s = Plus(Scaled(D_00317490, 1.0f - t), Scaled(s, t));
    U pos;
    func_00118558(time, step, 1.0f, out->r[3].q, start, source->r[3].q, end, &pos.q, anchor, 0);
    M3 w = Mul(Mul(m, s), *(M3 *)out);
    func_002BA818((VECTOR *)&state->r[3], pos.q);
    *(M3 *)state = w;
    state->r[2].i[3] = 0;
    state->r[1].i[3] = 0;
    state->r[0].i[3] = 0;
    state->r[3].f[3] = 1.0f;
}
