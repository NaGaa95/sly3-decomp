// Per-frame update of the two effect references of a vehicle-like owner: the second effect (+0x3F4) is created while the owner moves fast or busy
// (state 4 skips this), the first (+0x3E8) while the owner is in an active state; its level is smoothed towards |speed| * 0.00125 and clamped to 0..1.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct VTE { short delta, pad; void *fn; };
struct Fx { char pad00[0x44]; int f44; char pad48[0x14]; unsigned short h5C; unsigned short h5E; };
struct Actor { char pad00[0x18]; unsigned int flags; };
struct Ref { Fx *obj; int id; };
struct CLQ { float g0, g1, g2, gUnused; };
struct Owner {
    char pad00[0xC]; VTE *vt;
    char pad10[0x134 - 0x10]; Actor *actor;
    char pad138[0x33C - 0x138]; float g33C;
    char pad340[0x380 - 0x340]; int state;
    char pad384[0x3E8 - 0x384]; Ref ref1; float g3F0; Ref ref2; int flag3FC;
};
struct CLOCK { float now, step; };
extern CLOCK D_0036BB98;
extern CLQ D_00325740, D_00325750;
extern char D_00325728[];
extern "C" {
int func_00205A38(Owner *);
int func_001A7A80(Actor *, int, float);
void func_002051F0(Owner *);
void func_00205198(Owner *);
Fx *func_002459F8(int);
void func_00244F08(Fx *, Owner *);
void func_002BBCD8(Ref *, Fx *);
void func_00245100(Fx *, float, float);
float func_0011E598(float, float, float, void *, float *);
void func_00244E08(Fx *, float);
void func_00244ED0(Fx *, float);
}
static inline qword Length(qword v)
{
    qword d, one, len;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(len) : "j"(d));
    return len;
}
static inline float X(qword v)
{
    qword t;
    float f;
    __asm__("qmfc2.ni %0,%1" : "=r"(t) : "j"(v));
    __asm__("mtc1 %1,%0" : "=f"(f) : "r"(t));
    return f;
}
static inline float GClampR(float g, float gMin, float gMax) { if (g < gMin) return gMin; if (gMax < g) return gMax; return g; }
static inline float Curve(const CLQ &c, float t) { return c.g0 + t * (c.g1 + t * c.g2); }
extern "C" void func_00204E00(Owner *self)
{
    int moving = 0;
    if (self->state != 4) {
        int idle = func_00205A38(self) == 0;
        if (idle) {
            if (self->flag3FC) {
                int busy = func_001A7A80(self->actor, 0xE0, 0.0f);
                if (self->ref2.obj) {
                    if (busy)
                        func_002051F0(self);
                    moving = 1;
                } else {
                    moving = busy != 0;
                }
            } else {
                VTE *e = &self->vt[38];
                qword velocity = ((qword (*)(void *))e->fn)((char *)self + e->delta);
                if (350.0f < X(Length(velocity)))
                    moving = 1;
            }
        }
        self->flag3FC = idle;
    }
    if (self->ref2.obj) {
        Fx *fx = self->ref2.obj;
        bool r = false;
        if (fx->f44 == 0) {
            bool busy = fx->h5E || (fx->h5C & 1);
            r = !busy;
        }
        if (r)
            moving = 0;
    }
    if (moving) {
        Ref *ref2 = &self->ref2;
        func_00205198(self);
        if (!self->ref2.obj && self->ref2.id != -1) {
            Fx *fx = func_002459F8(self->ref2.id);
            func_00244F08(fx, self);
            func_002BBCD8(ref2, fx);
        }
    } else {
        func_002051F0(self);
    }
    int active = 0;
    switch (self->state) {
    case 1:
        if (self->actor->flags & 0xE0)
            active = 1;
        break;
    case 2:
    case 3:
        if (self->g33C != 0.0f)
            active = 1;
        break;
    }
    if (active && !moving) {
        Ref *ref1 = &self->ref1;
        func_002051F0(self);
        if (!self->ref1.obj) {
            if (self->ref1.id != -1) {
                Fx *fx = func_002459F8(self->ref1.id);
                func_00244F08(fx, self);
                func_002BBCD8(ref1, fx);
                func_00245100(self->ref1.obj, 150.0f, 1000.0f);
            }
            if (!self->ref1.obj)
                return;
        }
        self->g3F0 = func_0011E598(self->g3F0, __builtin_fabsf(self->g33C) * 0.00125f, D_0036BB98.step, D_00325728, 0);
        self->g3F0 = GClampR(self->g3F0, 0.0f, 1.0f);
        func_00244E08(self->ref1.obj, self->g3F0);
        float v;
        if ((self->state == 1 && (self->actor->flags & 0x40)) || self->state == 2)
            v = Curve(D_00325740, self->g3F0);
        else
            v = Curve(D_00325750, self->g3F0);
        func_00244ED0(self->ref1.obj, v);
    } else {
        func_00205198(self);
    }
}
