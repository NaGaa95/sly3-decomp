// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00230C70: one simulation step of a rope-like path chain (Sly 3 version of Sly 2 func_001E9090). Point 0 is the start offset in the first
// space (velocity from func_0028BCD0); every later point is integrated (accel = force - damping * v, v += accel * dt, pos += (v_old + v_new) * dt / 2),
// pulled back to the rest distance |dist[i] - dist[i - 1]| of the previous point along the normalized displacement (fallback D_00317530) and the
// relative velocity along it is removed. In mode 2 the last point is pinned to the end offset in the last space, its velocity is projected on the
// direction to its neighbour, and func_00231240 extends the path. Finally every point is transformed into the path's local space.
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
struct VV { qword q; VV() {} VV(const qword &v) { q = v; } operator qword() const { return q; } };
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
struct M4 { qword r[4]; };
struct SPACE { char pad[0x40]; M4 matrix; };
struct VT { short delta, pad; M4 *(*fn)(void *); };
struct PATH { char pad[0xC]; VT *vt; char pad10[0xD8 - 0x10]; int count; int padDC; float *dist; U *pos; };
struct CHAIN
{
    qword force;
    qword pad10;
    qword start;
    qword end;
    SPACE *first;
    SPACE *last;
    PATH *path;
    int mode;
    int pad50;
    U *position;
    U *velocity;
    float *distance;
    float damping;
};
struct CLOCK { float t, dt; };
extern CLOCK D_0036BB98;
extern qword D_00317530;
extern "C" {
qword func_0028BCD0(SPACE *, SPACE *, qword);
M4 *func_0011D768(M4 *, M4 *);
void func_00231240(CHAIN *, float);
void func_0022DCB8(PATH *);
void func_00230C70(CHAIN *);
}
static inline VV TransformPoint(const M4 &m, VV v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %1, %5x\n\tvmadday.xyz $ACC, %2, %5y\n\tvmaddaz.xyz $ACC, %3, %5z\n\tvmaddw.xyz %0, %4, $vf0w"
            : "=j"(r) : "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]), "j"(m.r[3]), "j"(v));
    return r;
}
static inline VV Sub(VV a, VV b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline float GFromVf(VV v) { float g; __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(v)); return g; }
static inline float GFromQw(qword q) { float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(q)); return g; }
static inline VV Sqrt(VV v) { qword r; __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(r) : "j"(v)); return r; }
static inline VV Dot(VV a, VV b)
{
    qword r, one;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(r), "=j"(one) : "j"(a), "j"(b));
    return r;
}
static inline VV Length(VV v) { return Sqrt(Dot(v, v)); }
static inline VV DivideQ(VV v, VV l) { qword r; __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(l), "j"(v)); return r; }
static inline VV AddScaled(VV base, VU_FLOAT g, VV v)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %3, %2x"
            : "=j"(r) : "j"(base), "j"(g.q), "j"(v));
    return r;
}
static inline VV NormalizeSafe(VV v, VV fallback)
{
    VV len = Length(v);
    if (GFromVf(len) < 0.0001f)
        return fallback;
    return DivideQ(v, len);
}
static inline VV VecCombo3(VV base, VU_FLOAT g1, VV v1, VU_FLOAT g2, VV v2)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddax.xyzw $ACC, %3, %2x\n\tvmaddx.xyzw %0, %5, %4x"
            : "=j"(r) : "j"(base), "j"(g1.q), "j"(v1), "j"(g2.q), "j"(v2));
    return r;
}
static inline VV MulX(VV v, VV s) { qword r; __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(v), "j"(s)); return r; }
static inline float Abs(float g) { return __builtin_fabsf(g); }

void func_00230C70(CHAIN *p)
{
    float dt = D_0036BB98.dt;
    VV prev = TransformPoint(p->first->matrix, p->start);
    int n = p->path->count;
    p->position[0].q = prev;
    U *velocity = p->velocity;
    VV prevVel = func_0028BCD0(p->first, 0, prev);
    velocity[0].q = prevVel;
    int i;
    for (i = 1; i < n; i++)
    {
        VV accel = AddScaled(p->force, VU_FLOAT(-p->damping), p->velocity[i].q);
        VV vel = AddScaled(p->velocity[i].q, VU_FLOAT(dt), accel);
        VV pos = VecCombo3(p->position[i].q, VU_FLOAT(dt * 0.5f), p->velocity[i].q, VU_FLOAT(dt * 0.5f), vel);
        VV delta = Sub(pos, prev);
        VV dir = NormalizeSafe(delta, D_00317530);
        float proj = -GFromQw(Dot(Sub(vel, prevVel), dir));
        float d = Abs(p->distance[i] - p->distance[i - 1]);
        prev = AddScaled(prev, VU_FLOAT(d), dir);
        prevVel = AddScaled(vel, VU_FLOAT(proj), dir);
        p->position[i].q = prev;
        p->velocity[i].q = prevVel;
    }
    if (p->mode == 2)
    {
        p->position[n - 1].q = TransformPoint(p->last->matrix, p->end);
        if (n > 1)
        {
            VV dir = NormalizeSafe(Sub(p->position[n - 2].q, p->position[n - 1].q), D_00317530);
            p->velocity[n - 1].q = MulX(dir, Dot(p->velocity[n - 2].q, dir));
        }
        func_00231240(p, p->distance[n - 2] + GFromVf(Length(Sub(p->position[n - 2].q, p->position[n - 1].q))));
        n = p->path->count;
    }
    M4 inverse;
    {
        PATH *path = p->path;
        VT *e = &path->vt[36];
        func_0011D768(&inverse, e->fn((char *)path + e->delta));
    }
    for (i = 0; i < n; i++)
    {
        PATH *path = p->path;
        path->pos[i].q = TransformPoint(inverse, p->position[i].q);
    }
    func_0022DCB8(p->path);
}
