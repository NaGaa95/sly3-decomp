// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct M3 { qword r[3]; };
struct M4 { qword r[4]; };
union U { qword q; float f; };
class World {
public:
    int a[3];
    virtual void V1(); virtual void V2(); virtual void V3(); virtual void V4(); virtual void V5(); virtual void V6(); virtual void V7(); virtual void V8();
    virtual void V9(); virtual void V10(); virtual void V11(); virtual void V12(); virtual void V13(); virtual void V14(); virtual void V15(); virtual void V16();
    virtual void V17(); virtual void V18(); virtual void V19(); virtual void V20(); virtual void V21(); virtual void V22(); virtual void V23(); virtual void V24();
    virtual void V25(); virtual void V26(); virtual void V27(); virtual void V28(); virtual void V29(); virtual void V30(); virtual void V31(); virtual void V32();
    virtual void V33(); virtual void V34(); virtual void V35();
    virtual M4 *V36();
};
struct CLQ { float g0, g1, g2, gUnused; };
struct SPIN { char pad[0x40]; qword axis; };
struct Self {
    char pad0[0x20]; CLQ a; CLQ b;
    M3 mat; char pad70[0xF0 - 0x70]; SPIN *spin; char padF4[0x100 - 0xF4]; qword pos;
};
struct Out { qword pos; M3 mat; float clamped; float curve; };
struct LM { float gMin, gMax; };
extern LM D_00341FF0;
extern char D_00475480[];
extern "C" {
World *func_00165B28(void *);
M3 func_0011CFC0(const M3 &, const M4 *);
void func_0011D0B8(M3 *, float *, qword *);
M3 func_0011C8C0(qword, float);
qword func_00167838(World *, qword);
void func_0020DC48(Self *, float, qword, Out *);
}
static inline M3 Mul(const M3 &a, const M3 &b) return r {
 __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[0]):"j"(a.r[0]),"j"(a.r[1]),"j"(a.r[2]),"j"(b.r[0]));
 __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[1]):"j"(a.r[0]),"j"(a.r[1]),"j"(a.r[2]),"j"(b.r[1]));
 __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[2]):"j"(a.r[0]),"j"(a.r[1]),"j"(a.r[2]),"j"(b.r[2]));
}
static inline float Curve(const CLQ &c, float t) { return c.g0 + t * (c.g1 + t * c.g2); }
static inline float Clamp(float g, const LM &lm) { float gMin = lm.gMin, gMax = lm.gMax; if (g < gMin) return gMin; if (gMax < g) return gMax; return g; }
extern "C" void func_0020DC48(Self *p, float dt, qword unused, Out *out)
{
    World *world = func_00165B28(D_00475480);
    M3 camera = func_0011CFC0(p->mat, world->V36());
    U axis;
    float angle;
    func_0011D0B8(&camera, &angle, &axis.q);
    M3 fade = func_0011C8C0(axis.q, angle * dt);
    M3 spin = func_0011C8C0(p->spin->axis, (dt + dt) * 3.14159274f);
    out->pos = func_00167838(world, p->pos);
    out->mat = Mul(Mul(fade, spin), p->mat);
    out->clamped = Clamp(Curve(p->b, dt), D_00341FF0);
    out->curve = Curve(p->a, dt);
}
