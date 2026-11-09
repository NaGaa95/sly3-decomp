// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// SLY3_ASFIX: engine-divfix1
// Vehicle wheel update (Sly 3 form of Sly 2 func_001D41F8): every wheel is lifted to its contact height, spun by the
// drive or by the ground speed, its node is re-posed and, when it has a dust effect, the effect is aimed and scaled.
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
struct M3 { U r[3]; };
struct M4 { M3 basis; U position; };
struct NODE { M4 matrix, local; char pad80[0x20]; NODE *parent; int generation; };
struct CONTACT { char pad0[0x10]; U point; char pad20[0x70]; float height; };
struct VE { short delta, pad; void *fn; };
struct FX { char pad0[0xC]; VE *vt; };
struct SLOT { char pad0[0x68]; float amount; };
struct FXBLOCK { char pad0[0x40]; float low, high; };
struct REF;
struct VV { qword q; VV() {} VV(const qword &v) { q = v; } operator qword() const { return q; } };
struct ENTRY {
    NODE *node; char pad4[4]; float tilt, speed, angle, radius; char pad18[8]; U target; char pad30[0x18];
    float height; char pad4C[4]; FX *fx; char pad54[0xC];
};
struct P {
    char pad0[0xC]; VE *vt; char pad10[0x40]; NODE *space; char pad54[0x13C]; ENTRY entries[4];
    char pad310[0x1C]; float slipForward, slipReverse; char pad334[8]; float drive; char pad340[0x40]; int state;
    char pad384[0x10]; float steer;
};
struct CLOCK { float time, dt; };
struct GAME { char pad[0x44F4]; int generation; };
extern CLOCK D_0036BB98;
extern GAME D_00475480;
extern qword D_00317540, D_00317550, D_00317560;
extern char D_00325808[], D_00325818[], D_00325828[];
extern "C" {
qword func_001C94E8(int, P *, qword);
qword func_0028E910(NODE *, NODE *, qword);
void *func_00205840(P *, ENTRY *);
float func_0011E598(float, float, float, void *, float *);
float func_0011E3B8(float);
M3 *func_0011C8C0(M3 *, qword, float);
qword *func_002BA818(qword *, qword);
void func_0028E768(P *);
void func_0023CC40(P *);
SLOT *func_001FE9B8(FX *);
FX *func_001FE950(FX *, int);
void func_002BEBD0(FX **, FX *);
qword func_0028E990(NODE *, NODE *, qword);
M3 *func_0011CBA0(M3 *, qword);
FXBLOCK *func_001FD6A0(FX *, int);
}
struct REF {
    FX *fx;
    int pad;
    REF() { fx = 0; }
    ~REF() { if (fx) ((void (*)(void *))fx->vt[2].fn)((char *)fx + fx->vt[2].delta); }
    void operator=(FX *p) { func_002BEBD0(&fx, p); }
    operator FX *() const { return fx; }
};
static inline VV Scalar(float f) { VV r; __asm__("qmtc2 %1,%0" : "=j"(r.q) : "r"(f)); return r; }
static inline VV Scale(VV a, VV b) { qword r; __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline VV Cross(VV a, VV b) { qword r; __asm__("vopmula.xyz $ACC,%1,%2\n\tvopmsub.xyz %0,%2,%1" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline float Clamp(float v, float low, float high) { if (v < low) return low; else if (high < v) return high; else return v; }
static inline float Abs(float f) { return __builtin_fabsf(f); }
static inline M3 FrameFrom(qword forward) return r { func_0011CBA0(&r, forward); }
static inline M3 Rotation(qword axis, float angle) return r { func_0011C8C0(&r, axis, angle); }
static inline M3 Mul(const M3 &a, const M3 &b) return r {
    qword x = a.r[0].q, y = a.r[1].q, z = a.r[2].q;
    __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z" : "=j"(r.r[0].q) : "j"(x), "j"(y), "j"(z), "j"(b.r[0].q));
    __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z" : "=j"(r.r[1].q) : "j"(x), "j"(y), "j"(z), "j"(b.r[1].q));
    __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z" : "=j"(r.r[2].q) : "j"(x), "j"(y), "j"(z), "j"(b.r[2].q));
}
extern "C" void func_00206FD8(P *p)
{
    U velocity, point, target;
    M3 basis;
    if (p->state == 4)
        velocity.q = D_00317560;
    else {
        VE *method = &p->vt[38];
        velocity.q = func_001C94E8(0, p, ((qword (*)(P *))method->fn)((P *)((char *)p + method->delta)));
    }
    for (int i = 0; i < sizeof(p->entries) / sizeof(p->entries[0]); i++) {
        ENTRY *e = &p->entries[i];
        point.q = func_0028E910(0, p->space, e->node->local.position.q);
        void *hit = func_00205840(p, e);
        {
            float height;
            if (hit) {
                float limit = e->height + ((CONTACT *)hit)->height;
                if (point.f[2] < limit) { point.f[2] = limit; goto heightDone; }
                height = limit;
            } else
                height = e->height;
            point.f[2] = func_0011E598(point.f[2], height, D_0036BB98.dt, D_00325808, 0);
        }
        heightDone:;
        point.q = func_0028E910(p->space, e->node->parent, point.q);
        if (e->node->parent == p->space)
            target.q = e->target.q;
        else
            target.q = func_0028E910(p->space, e->node->parent, e->target.q);
        point.f[0] = target.f[0];
        point.f[1] = target.f[1];
        float desired;
        if (i < 2) desired = 0.0f; else desired = p->drive / e->radius;
        if (hit) {
            float current = velocity.f[0] / e->radius;
            if (!(i < 2)) current += p->steer;
            if ((0.0f < desired && current < 0.25f * desired) || (desired < 0.0f && 0.25f * desired < current))
                e->speed = func_0011E598(e->speed, 0.25f * desired, D_0036BB98.dt, D_00325818, 0);
            else
                e->speed = current;
        } else {
            float goal = desired;
            if (!(i < 2)) goal += p->steer;
            float dt = D_0036BB98.dt;
            void *table;
            if (Abs(e->speed) < Abs(desired)) table = D_00325818; else table = D_00325828;
            e->speed = func_0011E598(e->speed, goal, dt, table, 0);
        }
        e->angle = func_0011E3B8(e->angle + e->speed * D_0036BB98.dt);
        basis = Mul(Rotation(D_00317550, e->tilt), Rotation(D_00317540, e->angle));
        NODE *node = e->node;
        func_002BA818(&node->matrix.position.q, point.q);
        node->matrix.basis = basis;
        node->matrix.position.f[3] = 1.0f;
        node->matrix.basis.r[1].f[3] = 0.0f;
        node->matrix.basis.r[0].f[3] = 0.0f;
        node->matrix.basis.r[2].f[3] = 0.0f;
        int generation = ++D_00475480.generation;
        e->node->generation = generation;
        FX *wheel = e->fx;
        if (wheel) {
            REF ref;
            SLOT *slot = func_001FE9B8(wheel);
            ref = func_001FE950(wheel, 0x78E);
            if (slot && ref) {
                if (hit) {
                    M3 frame;
                    ((void (*)(void *, qword))wheel->vt[34].fn)((char *)wheel + wheel->vt[34].delta, ((CONTACT *)hit)->point.q);
                    VV axle = func_0028E990(e->node, 0, basis.r[1].q);
                    VV forward = Cross(p->space->local.basis.r[2].q, axle);
                    if (e->speed < 0.0f)
                        forward = Scale(forward, Scalar(-1.0f));
                    frame = FrameFrom(forward);
                    ((void (*)(void *, M3))wheel->vt[35].fn)((char *)wheel + wheel->vt[35].delta, frame);
                    float spin = Abs(e->radius * e->speed);
                    FXBLOCK *block = func_001FD6A0(ref, 1);
                    block->low = spin * 0.9f;
                    block->high = spin * 1.1f;
                    float limit = e->speed < 0.0f ? p->slipReverse : p->slipForward;
                    slot->amount = Clamp(spin / limit, 0.0f, 1.0f);
                } else
                    slot->amount = 0.0f;
            }
        }
    }
    if (p->state != 4)
        func_0028E768(p);
    func_0023CC40(p);
}
