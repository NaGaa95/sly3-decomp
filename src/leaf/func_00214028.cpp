// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Per-frame drive of a floating body (states 2, 4, 5): lift toward the target height g228 from the frame-local velocity,
// a turn about z, the predicted position one step ahead, a push toward the turned side offset, and a spring toward the
// world position at height g248 (+ g24C in states 5/6), each handed to func_00244890 / func_00244828.
// The position is read into a local before the step splat is built and the velocity through a plain pointer, so the
// splat's dead stack temporary lands between the two loads as in the original.
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
struct M3 { qword r[3]; };
struct MATRIX4 { qword r[4]; };
#define VF1(n) virtual void V##n();
struct LO {
    int hdr[3];
    VF1(1) VF1(2) VF1(3) VF1(4) VF1(5) VF1(6) VF1(7) VF1(8) VF1(9) VF1(10) VF1(11) VF1(12) VF1(13) VF1(14) VF1(15) VF1(16)
    VF1(17) VF1(18) VF1(19) VF1(20) VF1(21) VF1(22) VF1(23) VF1(24) VF1(25) VF1(26) VF1(27) VF1(28) VF1(29) VF1(30) VF1(31)
    VF1(32) VF1(33) VF1(34) VF1(35)
    virtual MATRIX4 *PmatWorld();                                // 36
    VF1(37)
    virtual qword AngularVelocity();                             // 38
};
struct BODY { char pad0[0xA0]; void *space; char padA4[0xB0 - 0xA4]; qword position; char padC0[0xF0 - 0xC0]; qword velocity; };
struct FRAME { M3 basis; qword pad30; M3 local; char pad70[0xB0 - 0x70]; qword vec; };
struct SO : LO {
    char pad10[0x48 - 0x10]; BODY *body; FRAME *frame;
    char pad50[0x1B0 - 0x50]; int state; char pad1B4[0x1DC - 0x1B4]; float *wake; char pad1E0[0x224 - 0x1E0];
    float g224, g228; char pad22C[0x248 - 0x22C]; float g248, g24C;
};
struct CLOCK { float time, dt; };
extern CLOCK D_0036BB98;
extern qword D_00317550;
extern char D_00325BA8[];
extern "C" {
void func_00243738(SO *);
void func_00244890(SO *, qword);
void func_00244828(SO *, qword);
M3 func_0011C8C0(qword, float);
qword func_0028E990(void *, void *, qword);
qword func_001205F0(float);
void func_00120C80(qword, qword, void *, qword *, float);
}
static inline float GetZ(qword v) { float f; __asm__("pextuw %0,$0,%1" : "=r"(f) : "r"(v)); return f; }
struct VU_FLOAT { qword q; VU_FLOAT() {} };
static inline VU_FLOAT ScalarFromWord(const float &f) { VU_FLOAT g; __asm__("qmtc2.ni %1,%0" : "=j"(g.q) : "rV"(*(const int *)&f)); return g; }
static inline qword Gpr(qword v)
{
    register qword r __asm__("$4"); // pin: the original copies the result through $a0
    __asm__("qmfc2.ni %0,%1" : "=r"(r) : "j"(v));
    return r;
}
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }

static inline qword Div(qword v, VU_FLOAT l) { qword r; __asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q" : "=j"(r) : "j"(l.q), "j"(v)); return r; }
static inline qword AddScaled(qword a, qword b, VU_FLOAT s)
{
    qword r;
    __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(a), "j"(b), "j"(s.q));
    return r;
}
static inline qword MulM3(const M3 &m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC,%2,%1x\n\tvmadday.xyz $ACC,%3,%1y\n\tvmaddz.xyz %0,%4,%1z" : "=j"(r) : "j"(v), "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]));
    return r;
}
static inline qword MulT(const M3 *m, qword v)
{
    qword r, a, b, c, one;
    __asm__("vmul.xyzw %2, %5, %8\n\tvmaxw.xyzw %1, $vf0, $vf0w\n\tvmul.xyzw %3, %6, %8\n\tvmul.xyzw %4, %7, %8\n\tvadday.x $ACC, %2, %2y\n\tvmaddz.x %0, %1, %2z\n\tvaddax.y $ACC, %3, %3x\n\tvmaddz.y %0, %1, %3z\n\tvaddax.z $ACC, %4, %4x\n\tvmaddy.z %0, %1, %4y"
            : "=j"(r), "=&j"(one), "=&j"(a), "=&j"(b), "=&j"(c) : "j"(m->r[0]), "j"(m->r[1]), "j"(m->r[2]), "j"(v));
    return r;
}
extern "C" void func_00214028(SO *self)
{
    func_00243738(self);
    switch (self->state) {
    case 2:
    case 4:
    case 5: {
        FRAME *frame = self->frame;
        U local;
        local.q = MulT(&frame->basis, frame->vec);
        float zero = 0.0f;
        U lift;
        lift.f[1] = zero;
        lift.f[0] = zero;
        lift.f[2] = (self->g228 - local.f[2]) / D_0036BB98.dt;
        U push;
        push.q = MulM3(frame->local, lift.q);
        func_00244890(self, push.q);
        float half = D_0036BB98.dt * 0.5f;
        M3 rot;
        rot = func_0011C8C0(D_00317550, (local.f[2] + lift.f[2] * half) * D_0036BB98.dt);
        BODY *body = self->body;
        qword position = body->position;
        qword *pvel = &body->velocity;
        U next;
        next.q = AddScaled(position, *pvel, ScalarFromWord(D_0036BB98.dt));
        U at;
        at.q = func_0028E990(self->body->space, self->frame, next.q);
        U side;
        side.f[0] = self->g224;
        side.f[1] = zero;
        side.f[2] = zero;
        side.q = MulM3(rot, side.q);
        U vel0, drive, vel;
        qword r = Div(Sub(side.q, at.q), ScalarFromWord(D_0036BB98.dt));
        vel0.q = Gpr(r);
        if (self->wake)
            vel.q = func_001205F0(self->wake[2]);
        else
            vel.q = r;
        drive.q = func_0028E990(self->frame, 0, vel.q);
        drive.f[2] = 0.0f;
        func_00244828(self, drive.q);
        U pos;
        pos.q = self->PmatWorld()->r[3];
        pos.f[2] = self->g248;
        if ((unsigned)(self->state - 5) < 2)
            pos.f[2] = self->g248 + self->g24C;
        U out;
        func_00120C80(self->PmatWorld()->r[3], pos.q, D_00325BA8, &out.q, D_0036BB98.dt);
        float az = GetZ(self->AngularVelocity());
        U spin;
        spin.f[0] = 0.0f;
        spin.f[1] = 0.0f;
        spin.f[2] = az;
        U res;
        res.q = Div(Sub(out.q, spin.q), ScalarFromWord(D_0036BB98.dt));
        func_00244828(self, res.q);
        break;
    }
    }
}
