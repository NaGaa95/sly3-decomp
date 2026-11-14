// func_001ACE40: new C; relative/residual/gain are reload spill slots (0xC0/0xD0/0xE0).
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31
typedef int qword __attribute__((mode(TI)));
#define AT(p, off, type) (*(type *)((char *)(p) + (off)))
typedef union { qword q; float f[4]; } U;
struct M3 { U r[3]; };
struct M4 { U r[4]; };
struct LM { float lo, hi; };
struct CLOCK { float t, dt; };
struct MODEL { char pad[0x1C]; float base; char pad20[0x20]; float scale; };
struct DV { char pad[0x20]; qword value; };
struct WORK { union { struct M4 predicted; U scalar; } phase; struct M4 transform; U axis; struct M3 rotation; };
extern struct CLOCK g_clock;
extern qword D_003225C0;
extern struct LM D_003225D0, D_003225D8;
int func_0013B500(void *p, int n);
void func_0024E920(char *p, void *q);
void func_0028F680(void *a, void *b, struct M4 *pm, struct M4 *pm2, float g);
qword func_0028E910(void *a, void *b, qword v);
qword func_0028E990(void *a, void *b, qword v);
float func_002A3EE8(float y, float x);
float func_0011EE68(struct LM *plm, float g);
void func_0011C9E8(struct M3 *pm, qword v);
void func_002BA818(qword *pv, qword v);
void func_0012FE90(struct DV *pdv, qword v);
static inline float GMin(float a, float b) { return a < b ? a : b; }
static inline qword Point(struct M4 *m, qword *v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %1, %5x\n\tvmadday.xyz $ACC, %2, %5y\n\tvmaddaz.xyz $ACC, %3, %5z\n\tvmaddw.xyz %0, %4, $vf0w"
            : "=j"(r) : "j"(m->r[0].q), "j"(m->r[1].q), "j"(m->r[2].q), "j"(m->r[3].q), "j"(*v));
    return r;
}
static inline qword Origin(struct M4 *m, qword *v)
{
    qword r, pv = *v;
    /* the second "j"(pv) operand is allocation-only (raises pv's local-alloc priority) */
    __asm__("vmulax.xyz $ACC, %1, %2x\n\tvmadday.xyz $ACC, %3, %2y\n\tvmaddaz.xyz $ACC, %4, %2z\n\tvmaddw.xyz %0, %5, $vf0w"
 : "=j"(r) : "j"(m->r[0].q), "j"(pv), "j"(m->r[1].q), "j"(m->r[2].q), "0"(m->r[3].q), "j"(pv));
    return r;
}
static inline float X(qword q) { float x; __asm__("mtc1 %1, %0" : "=f"(x) : "r"(q)); return x; }
static inline float Z(qword q) { float r; __asm__("pextuw %0, $0, %1" : "=r"(r) : "r"(q)); return r; }
static inline qword Pack(float x, float y, float z)
{
    qword q, t;
    __asm__("mfc1 %0, %2\n\tmfc1 %1, %3\n\tpextlw %0, %1, %0\n\tmfc1 %1, %4\n\tpcpyld %0, %1, %0" : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z));
    return q;
}
static inline qword Add(qword a, qword b) { qword r; __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword SubT(qword a, qword b) { __asm__("vsub.xyzw %0, %0, %1" : "+j"(a) : "j"(b)); return a; }
static inline qword SubR(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword AddT(qword a, qword b) { __asm__("vadd.xyzw %0, %0, %1" : "+j"(a) : "j"(b)); return a; }
static inline float Length(qword v)
{
    qword d, one, r;
    float g;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(r) : "j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(r));
    return g;
}
static inline qword Bits(float f) { qword q; __asm__("mfc1 %0, %1" : "=r"(q) : "f"(f)); return q; }
static inline void Decay(char *p, int off, struct WORK *pw, qword g)
{
    qword v; struct DV *dv;
    pw->phase.scalar.q = g;
    dv = AT(p, off, struct DV *);
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(v) : "j"(dv->value), "j"(g));
    func_0012FE90(dv, v);
}
void func_001ACE40(char *p)
{
    struct WORK w;
    struct MODEL *m = AT(p, 0x113C, struct MODEL *);
    float ratio = (AT(p, 0x1C30, float) - m->base) / m->scale;
    if (AT(p, 0x11B4, void *) && func_0013B500(AT(p, 0x11B4, void *), 0x3A)) {
        float zero = 0.0f;
        if (zero < ratio) {
            char *o = AT(p, 0x11B4, char *);
            if (AT(o, 0x4AC, void *)) {
                qword mapped, tilt, axis, relative, residual;
                float heading;
                struct M4 *frame;
                void *space;
                char *group;
                func_0024E920(p, AT(o, 0x4AC, void *));
                func_0028F680(AT(AT(o, 0x4AC, char *), 0x194, void *), 0, &w.phase.predicted, 0, GMin(0.15f, ratio));
                mapped = func_0028E910(0, AT(p, 0x50, void *), Point(&w.phase.predicted, &D_003225C0));
                heading = func_002A3EE8(-Z(mapped), X(mapped) * 0.75f);
                heading = func_0011EE68(&D_003225D0, heading);
                tilt = Pack(zero, heading, zero);
                w.axis.q = tilt;
                func_0011C9E8(&w.rotation, Add(AT(p, 0x1C70, qword), w.axis.q));
                frame = &w.transform;
                func_002BA818(&frame->r[3].q, AT(p, 0x1C60, qword));
                frame->r[0] = w.rotation.r[0];
                frame->r[1] = w.rotation.r[1];
                group = AT(p, 0x1AA0, char *);
                frame->r[2] = w.rotation.r[2];
                w.transform.r[2].f[3] = zero;
                w.transform.r[1].f[3] = zero;
                w.transform.r[0].f[3] = zero;
                frame->r[3].f[3] = 1.0f;
                space = AT(AT(group, 0x48, char *), 0xA0, void *);
                relative = SubT(mapped, Origin(&w.transform, (qword *)(p + 0x1C80)));
                heading = X(func_0028E990(AT(p, 0x50, void *), space, relative));
                heading = func_0011EE68(&D_003225D8, heading);
                axis = Pack(heading, zero, zero);
                w.axis.q = axis;
                residual = SubR(relative, func_0028E990(space, AT(p, 0x50, void *), w.axis.q));
                if (Length(SubT(AddT(AT(p, 0x1C60, qword), residual), AT(p, 0x1C50, qword))) < 120.0f) {
                    func_0012FE90(AT(p, 0x1B00, struct DV *), tilt);
                    func_0012FE90(AT(p, 0x1AF4, struct DV *), residual);
                    func_0012FE90(AT(p, 0x1B04, struct DV *), axis);
                    AT(p, 0x1C2C, int) = 1;
                    AT(p, 0x1C34, float) = g_clock.t;
                    return;
                }
            }
        }
    }
    {
        float remaining = AT(p, 0x1C34, float) + 0.25f - g_clock.t;
        float after = remaining - g_clock.dt;
        float zero = 0.0f;
        float gain;
        qword gq;
        if (zero < after)
            gain = after / remaining;
        else
            gain = zero;
        gq = Bits(gain);
        Decay(p, 0x1B00, &w, gq);
        Decay(p, 0x1AF4, &w, gq);
        Decay(p, 0x1B04, &w, gq);
        AT(p, 0x1C2C, int) = 0;
    }
}
