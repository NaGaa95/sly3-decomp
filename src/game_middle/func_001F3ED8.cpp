// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Follow-camera step: asks the target (vtable slot 85) for its desired look data `in`, filters the camera position,
// height (clamped to the target's height range, smoothed unless `flag` forces a snap) and two spring pairs towards
// the look direction (func_001F3E48), and writes the resulting camera frame to `out`.  `flag` (or a pending reset
// word at +0x154) snaps all state instead of smoothing.
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; int i[4]; };
struct VE { short delta, pad; void *fn; };
struct Clock { float time, step; };
struct Poly { float a, b, c; };
struct Range { float lo, hi; };
struct Look {
    float x0, x4, x8, padC;
    U q10;
    U q20;
    float x30, x34, x38, x3C, x40, x44;
    char smp[0x54 - 0x48];
    float x54, x58, x5C;
    int x60;
    float x64, x68;
    int flags;
    int x70, x74;
    qword dir;
};
struct Self { char pad0[0xC]; VE *vt; char pad10[0x4C - 0x10]; int x4C; char pad50[0x154 - 0x50]; int x154; };
struct State { U p0; U v10; U p20; U v30; U p40; U v50; char pad60[0xC]; float time; };
struct Out { U q0, q10, q20, q30; float x40, x44; int x48; float x4C, x50; int x54; int x58, x5C; };
extern "C" {
extern Clock D_0036BB98;
extern U D_00317560;
extern char D_00325080[];
extern Poly D_00325090;
extern Range D_00341FF0;
void func_00292034(void *, int, int);
float func_0011E598(float, float, float, void *, float *);
qword func_0011FD70(float, float, float);
qword func_00120C80(qword, qword, float, void *, qword *);
void func_001F3E48(qword, float, float, float, U *, U *);
}
static inline float GClamp(float g, float lo, float hi)
{
    float r;
    if (g < lo)
        r = lo;
    else if (hi < g)
        r = hi;
    else
        r = g;
    return r;
}
static inline qword LengthV(qword v)
{
    qword d, one;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=&j"(one) : "j"(v));
    __asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "+j"(d));
    return d;
}
static inline float GetZ(qword q) { float z; __asm__("pextuw %0, $0, %1" : "=r"(z) : "r"(q)); return z; }
static inline void Clear3(U *v) { v->f[2] = 0; v->f[1] = 0; v->f[0] = 0; }
static inline float GFromQw(qword q) { float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(q), "j"(q)); return g; }
extern "C" void func_001F3ED8(Self *self, int flag, State *state, Out *out)
{
    Look in;
    float dt;
    func_00292034(out, 0, 0x60);
    {
        float now = D_0036BB98.time;
        float old = state->time;
        state->time = now;
        dt = now - old;
    }
    if (self->x154) {
        self->x154 = 0;
        flag = 1;
    }
    {
        VE *e = &self->vt[85];
        ((void (*)(void *, Look *))e->fn)((char *)self + e->delta, &in);
    }
    if (flag)
        in.flags &= ~6;
    out->x54 = in.x60;
    out->x4C = in.x58;
    out->x50 = in.x5C;
    out->x40 = in.x30;
    out->x44 = in.x34;
    out->x58 = in.x70;
    out->x5C = in.x74;
    out->x48 = in.flags;
    if (!(in.flags & 2)) {
        float zp;
        {
            VE *e = &self->vt[36];
            U *m = ((U *(*)(void *))e->fn)((char *)self + e->delta);
            zp = GetZ(m[3].q);
        }
        if (!(in.flags & 4)) {
            float v;
            if ((in.flags & 0x10) && !flag)
                v = state->p0.f[2];
            else
                v = in.x8;
            v = GClamp(v, zp + in.x38, zp + in.x3C);
            if (flag)
                state->p0.f[2] = v;
            else
                state->p0.f[2] = func_0011E598(state->p0.f[2], v, dt, in.smp, 0);
        }
        state->p0.f[0] = in.x0;
        state->p0.f[1] = in.x4;
        state->p0.f[2] = GClamp(state->p0.f[2], zp + in.x40, zp + in.x44);
    }
    if (flag) {
        Clear3(&state->v10);
    } else {
        state->v10.q = func_00120C80(state->v10.q, D_00317560.q, dt, D_00325080, 0);
    }
    float sp;
    if (self->x4C == 0) {
        sp = 0.0f;
    } else {
        VE *e = &self->vt[39];
        qword vel = ((qword (*)(void *))e->fn)((char *)self + e->delta);
        float s = GFromQw(LengthV(vel));
        float k = GClamp(D_00325090.a + s * (D_00325090.b + s * D_00325090.c), D_00341FF0.lo, D_00341FF0.hi);
        sp = in.x54 * k;
    }
    in.dir = func_0011FD70(out->x4C + 3.14159265f, sp, 0.0f);
    if (flag) {
        state->p20.q = in.dir;
        Clear3(&state->v30);
        state->p40.q = in.q20.q;
        Clear3(&state->v50);
    } else {
        func_001F3E48(in.dir, in.x68, in.x64, dt, &state->p20, &state->v30);
        func_001F3E48(in.q20.q, in.x68, in.x64, dt, &state->p40, &state->v50);
    }
    {
        qword r;
        __asm__("vadd.xyzw %0,%1,%2" : "=j"(r) : "j"(state->p0.q), "j"(state->v10.q));
        __asm__("vadd.xyzw %0,%0,%1" : "+j"(r) : "j"(state->p20.q));
        out->q10.q = in.q10.q;
        out->q0.q = r;
    }
    out->q20.q = state->p20.q;
    out->q30.q = state->p40.q;
}
