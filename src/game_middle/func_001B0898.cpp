// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct M3 { qword r[3]; };
struct M4 { qword r[4]; };
static inline qword QwFromF(float g) { qword q; __asm__("mfc1 %0,%1" : "=r"(q) : "f"(g)); return q; }
static inline qword Sub(qword a, qword b)
{
    qword r;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline qword AddScaled(qword a, qword v, qword f)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %3, %2x" : "=j"(r) : "j"(a), "j"(f), "j"(v), "j"(f));
    return r;
}
static inline qword Transform(const M4 &m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %1, %5x\n\tvmadday.xyz $ACC, %2, %5y\n\tvmaddaz.xyz $ACC, %3, %5z\n\tvmaddw.xyz %0, %4, $vf0w" : "=j"(r) : "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]), "j"(m.r[3]), "j"(v));
    return r;
}
static inline qword TransformP(const M4 &m, const qword *v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %1, %5x\n\tvmadday.xyz $ACC, %2, %5y\n\tvmaddaz.xyz $ACC, %3, %5z\n\tvmaddw.xyz %0, %4, $vf0w" : "=j"(r) : "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]), "j"(m.r[3]), "j"(*v));
    return r;
}
struct VTE { short delta, pad; void *fn; };
struct VT { char pad[0x120]; VTE getMatrix; VTE getFrame; VTE getVel; };
struct SO {
    char pad0[0xC]; VT *vt; char pad10[0xD0 - 0x10]; SO *next; int padD4; int flags;
};
struct Scope { unsigned char unused_storage[16]; };
extern "C" {
extern qword D_00317550;
extern struct { SO *p; } D_00479AD8;
void func_0011C8C0(M3 *ret, qword axis, float g);
qword func_002BA818(void *p, qword v);
void func_0028F680(void *owner, void *a, float dt, M4 *out, void *b);
float func_001205C8(qword v);
float func_0011E3B8(float g);
void func_00120A00(qword center, qword p0, qword p1, void *z, float *t, float *dist);
void func_002BC490(void *p, int n);
}
static inline M4 *GetMatrix(SO *p)
{
    VTE *e = &p->vt->getMatrix;
    return ((M4 *(*)(void *))e->fn)((char *)p + e->delta);
}
static inline qword GetVelocityAndSetFrame(SO *p, M4 *out, qword early)
{
    VTE *e = &p->vt->getVel;
    void *fn = e->fn;
    short adj = e->delta;
    // Initialize the fourth frame row before calling the velocity method.
    out->r[3] = early;
    return ((qword (*)(void *))fn)((char *)p + adj);
}
static inline void *GetFrame(SO *p, M4 *out)
{
    VTE *e = &p->vt->getFrame;
    return ((void *(*)(void *, M4 *))e->fn)((char *)p + e->delta, out);
}

extern "C" void func_001B0898(SO *p, int mask, qword a, qword b, SO **out, float *outT, float heading_in, float dt_in, float cone_in)
{
    float heading = heading_in;
    float dt = dt_in;
    float cone = cone_in;
    SO *best = 0;
    float nearest = 300.0f;
    float bestT;
    M4 mat;
    qword position;
    M4 fx;
    Scope scope;
    M4 prediction;
    M4 *frame = &fx;
    qword early = QwFromF(dt);
    func_0011C8C0((M3 *)frame, D_00317550, heading);
    position = GetMatrix(p)->r[3];
    qword origin = AddScaled(position, GetVelocityAndSetFrame(p, &fx, early), early);
    func_002BA818(&mat.r[3], origin);
    mat.r[0] = fx.r[0];
    mat.r[1] = fx.r[1];
    mat.r[2] = fx.r[2];
    ((float *)&mat)[11] = 0.0f;
    ((float *)&mat)[15] = 1.0f;
    ((float *)&mat)[7] = 0.0f;
    ((float *)&mat)[3] = 0.0f;
    // The path endpoints are passed by address to the inline transform.
    qword pa = TransformP(mat, &a);
    qword pb = TransformP(mat, &b);
    bestT = ((float *)&mat)[11];
    for (SO *node = D_00479AD8.p; node; node = node->next) {
        float t, distance;
        if (!(node->flags & mask))
            continue;
        void *owner = GetFrame(node, frame);
        func_0028F680(owner, 0, dt, &prediction, 0);
        qword center = Transform(prediction, fx.r[3]);
        float angle = func_0011E3B8(func_001205C8(Sub(center, mat.r[3])) - heading);
        if (cone < angle)
            continue;
        func_00120A00(center, pa, pb, 0, &t, &distance);
        if (distance < nearest) {
            bestT = t;
            nearest = distance;
            best = node;
        }
    }
    *out = best;
    *outT = bestT;
    func_002BC490(&scope, 2);
}
