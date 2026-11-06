// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct M3 { qword r[3]; };
struct M4 { qword r[4]; };
#define VF1(n) virtual void V##n();
class LO {
public:
    int hdr[3];
    VF1(1) VF1(2) VF1(3) VF1(4) VF1(5) VF1(6) VF1(7) VF1(8) VF1(9) VF1(10) VF1(11) VF1(12) VF1(13) VF1(14) VF1(15) VF1(16)
    VF1(17) VF1(18) VF1(19) VF1(20) VF1(21) VF1(22) VF1(23) VF1(24) VF1(25) VF1(26) VF1(27) VF1(28) VF1(29) VF1(30) VF1(31) VF1(32)
    VF1(33)
    virtual void SetPosition(qword v);          // 34
    virtual void RotateToMat(M3 *m);            // 35
    virtual M4 *Matrix();                       // 36
    VF1(37) VF1(38) VF1(39)
    virtual void SetVelocity(qword v);          // 40
};
struct CLQ { float g0, g1, g2, gUnused; };
struct Owner { char pad0[0x18]; int flags; };
enum Phase { PHASE0, PHASE1, PHASE2, PHASE3 };
struct LM { float gMin, gMax; };
struct Self {
    char pad0[0x134]; Owner *owner;
    char pad138[0x210 - 0x138]; enum Phase phase;
    char pad214[4]; LO *attached; LO *target; float g220; int n224;
    char pad228[0x22C - 0x228]; float g22C; float g230; float g234;
    char pad238[0x240 - 0x238]; CLQ curve; LM limit;
    char pad258[0x27C - 0x258]; int n27C; int pad280; int n284;
};
struct Clock { float t; float dt; };
extern Clock D_0036BB98;
extern char D_00475480[];
extern "C" {
void func_00210410(Self *, int);
qword func_002105B0(Self *);
void *func_001FBE30(int, int);
void func_0025D940(void *, int, int, Self *, Self *, float);
int func_0013B500(void *, int);
qword func_0023ED38(void *);
qword func_00212480(float, qword, qword, qword);
void func_0014D1F0(void *, Self *);
void func_002100E8(Self *);
}
static inline float GClamp(float g, const LM &lm) { float gMin = lm.gMin, gMax = lm.gMax; if (g < gMin) return gMin; if (gMax < g) return gMax; return g; }
static inline float Curve(const CLQ &c, float t) { return c.g0 + t * (c.g1 + t * c.g2); }
extern "C" void func_002100E8(Self *self)
{
    int shaded;
    if (!self->n284)
        return;
    shaded = self->owner->flags >> 3;
    shaded &= 1;
    switch (self->phase) {
    case PHASE0:
        if (shaded)
            func_00210410(self, 1);
        break;
    case PHASE1: {
        float x;
        if (self->attached)
            self->attached->SetPosition(func_002105B0(self));
        if (shaded) {
            x = GClamp(Curve(self->curve, D_0036BB98.t - self->g230), self->limit);
            {
                int done = self->limit.gMax <= x;
                if (!done)
                    break;
            }
        }
        func_00210410(self, 2);
        break;
    }
    case PHASE2:
        if (self->n224 && self->target) {
            LO *o = (LO *)func_001FBE30(self->n224, 0);
            if (o) {
                o->SetPosition(self->target->Matrix()->r[3]);
                o->RotateToMat((M3 *)self->target->Matrix());
                func_0025D940(D_00475480, self->n27C, -1, self, self, 1.0f);
                if (func_0013B500(o, 0x2F)) {
                    o->SetVelocity(func_00212480(self->g220, self->target->Matrix()->r[3], func_002105B0(self), func_0023ED38(o)));
                    if (func_0013B500(o, 0x59))
                        func_0014D1F0(o, self);
                }
            }
        }
        self->g234 = D_0036BB98.t;
        func_00210410(self, 3);
        break;
    case PHASE3:
        if (!shaded && self->g22C < D_0036BB98.t - self->g234)
            func_00210410(self, 0);
        break;
    }
}
