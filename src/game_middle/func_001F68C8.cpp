// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Reset the motion state of a two-component object after its mode changed.
typedef int qword __attribute__((mode(TI)));
struct VTE { short delta; short pad; qword *(*method)(void *); };
struct COMP { char pad[0xB0]; qword accel; char padC0[0xF0 - 0xC0]; qword vel; };
struct HOLDER { char pad[0xC]; VTE *vt; };
struct SELF {
    char pad[0xC]; VTE *vt; void *owner; char pad14[0x48 - 0x14]; COMP *compA; COMP *compB;
    char pad50[0x130 - 0x50]; int mode;
};
extern "C" {
extern qword D_00346FD0;
extern char D_00346FE0[];
void func_00244828(SELF *, qword);
int func_0013B500(void *, int);
void func_0028F068(SELF *, COMP *, int);
void func_0011CCF8(qword *, int, void *);
void func_0023EDE8(SELF *, void *, void *);
void func_0028CA78(SELF *);
}
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1,%0" : "=j"(q) : "r"(f)); } };
static inline qword AddScaled(qword a, qword b, VU_FLOAT s)
{
    qword r;
    __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(a), "j"(b), "j"(s.q));
    return r;
}
extern "C" void func_001F68C8(SELF *self)
{
    float *pa = (float *)&self->compA->vel;
    pa[2] = 0;
    pa[1] = 0;
    pa[0] = 0;
    float *pb = (float *)&self->compB->vel;
    pb[2] = 0;
    pb[1] = 0;
    pb[0] = 0;
    switch (self->mode) {
    case 0:
    case 4: {
        COMP *c = self->compA;
        qword *pa = &c->accel;
        qword v = c->vel;
        c->vel = AddScaled(v, *pa, VU_FLOAT(-5.0f));
        break;
    }
    case 2:
    case 3:
        func_00244828(self, D_00346FD0);
        break;
    }
    if (self->owner && !func_0013B500(self->owner, 0x32)) {
        qword probe[3];
        func_0028F068(self, self->compB, 2);
        VTE *entry = &self->vt[36];
        func_0011CCF8(entry->method((char *)self + entry->delta), 0, probe);
        func_0023EDE8(self, probe, D_00346FE0);
    }
    func_0028CA78(self);
}
