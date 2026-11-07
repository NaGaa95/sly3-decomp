// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Ported from the Sly 2 source src/hand/func_001F9E70.cpp (ALO pending velocity changes applied, then half a frame
// of each change moves the position / turns the rotation).
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; int i[4]; };
struct M3 { U r[3]; M3() {} M3(const M3 &m) { r[0] = m.r[0]; r[1] = m.r[1]; r[2] = m.r[2]; } M3 &operator=(const M3 &m) { r[0] = m.r[0]; r[1] = m.r[1]; r[2] = m.r[2]; return *this; } };
struct OWNER { M3 matrix; U position; char pad40[0x60]; OWNER *parent; int stamp; char padA8[8]; U velocity; };
struct VT { short delta, pad; void (*fn)(void *); };
struct P { char pad0[0xC]; VT *vt; char pad10[0x38]; OWNER *position, *rotation; char pad50[0x88]; void *enabled; char padDC[4]; U force[2]; };
struct SW { char pad[0x44F4]; int stamp; };
extern SW D_00475480;
extern float D_0036BB9C;
extern qword D_00317560;
extern "C" int func_0011E9F0(float, float, float);
extern "C" void func_0028F260(P *, OWNER *);
extern "C" qword func_0028E990(void *, OWNER *, qword);
extern "C" void func_0023DD40(P *);
extern "C" qword *func_002BA818(qword *, qword);
extern "C" M3 *func_0011C930(M3 *, qword);
extern "C" void func_0011C798(M3 *);
static inline float X(qword q) { float f; __asm__("mtc1 %1,%0" : "=f"(f) : "r"(q)); return f; }
static inline float Y(qword q) { float f; __asm__("prot3w %0,%1" : "=r"(f) : "r"(q)); return f; }
static inline float Z(qword q) { float f; __asm__("pextuw %0,$0,%1" : "=r"(f) : "r"(q)); return f; }
static inline int FVecsNear(qword a, qword b)
{
    int f = 0;
    if (func_0011E9F0(X(a), X(b), 0.0001f))
        if (func_0011E9F0(Y(a), Y(b), 0.0001f))
            f = func_0011E9F0(Z(a), Z(b), 0.0001f) != 0;
    return f;
}
static inline qword Scalar(float f, U *out) { qword q; __asm__("qmtc2.ni %1,%0" : "=j"(q) : "r"(f)); out->q = q; return out->q; }
// The extra allocation-only "j"(b) operand tips regclass to VU for shift/turn, so (as in the target) they get no
// callee-saved GPR and live in stack spill slots (sp+0xD0 / sp+0xE0).
static inline qword Add(qword a, qword b) { qword r; __asm__("vadd.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b), "j"(b)); return r; }
static inline qword AddScaled(qword p, qword v, qword k) { __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%0,%2x" : "+j"(v) : "j"(p), "j"(k)); return v; }
static inline qword Scale(qword v, qword k) { __asm__("vmulx.xyzw %0,%0,%1x" : "+j"(v) : "j"(k)); return v; }
static inline qword Zero() { qword r; __asm__("vsub.xyzw %0,$vf0,$vf0" : "=j"(r)); return r; }
static inline M3 BuildRotation(qword v) return m { func_0011C930(&m, v); }
static inline M3 Mul(const M3 &a, const M3 &b) return r
{
    qword a0 = a.r[0].q, a1 = a.r[1].q, a2 = a.r[2].q;
    __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z" : "=j"(r.r[0].q) : "j"(a0), "j"(a1), "j"(a2), "j"(b.r[0].q));
    __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z" : "=j"(r.r[1].q) : "j"(a0), "j"(a1), "j"(a2), "j"(b.r[1].q));
    __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z" : "=j"(r.r[2].q) : "j"(a0), "j"(a1), "j"(a2), "j"(b.r[2].q));
}
extern "C" void func_00243A80(P *p)
{
    U scalar;
    M3 frame;
    qword shift, turn;
    if (!p->enabled)
        return;
    int changed = 0;
    OWNER *position = p->position, *rotation = p->rotation;
    if (!FVecsNear(D_00317560, p->force[0].q)) {
        func_0028F260(p, position);
        U *pending = &p->force[0];
        changed = 1;
        shift = func_0028E990(0, position->parent, pending->q);
        pending->i[2] = 0;
        pending->i[1] = 0;
        pending->i[0] = 0;
        position->velocity.q = Add(position->velocity.q, shift);
    } else
        shift = Zero();
    if (!FVecsNear(D_00317560, p->force[1].q)) {
        func_0028F260(p, rotation);
        U *pending = &p->force[1];
        changed = 1;
        turn = func_0028E990(0, rotation->parent, pending->q);
        pending->i[2] = 0;
        pending->i[1] = 0;
        pending->i[0] = 0;
        rotation->velocity.q = Add(rotation->velocity.q, turn);
    } else
        turn = Zero();
    if (!changed)
        return;
    func_0023DD40(p);
    if (!FVecsNear(D_00317560, shift)) {
        qword pt = position->position.q;
        qword k = Scalar(D_0036BB9C * 0.5f, &scalar);
        func_002BA818(&position->position.q, AddScaled(pt, shift, k));
        position->position.f[3] = 1.0f;
        position->stamp = ++D_00475480.stamp;
    }
    if (!FVecsNear(D_00317560, turn)) {
        frame = Mul(BuildRotation(Scale(turn, Scalar(D_0036BB9C * 0.5f, &scalar))), rotation->matrix);
        func_0011C798(&frame);
        rotation->matrix = frame;
        rotation->matrix.r[1].i[3] = 0;
        rotation->matrix.r[2].i[3] = 0;
        rotation->matrix.r[0].i[3] = 0;
        rotation->stamp = ++D_00475480.stamp;
    }
    p->vt[20].fn((char *)p + p->vt[20].delta);
}
