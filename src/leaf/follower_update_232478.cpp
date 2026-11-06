// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Follower per-frame update: run the base update, then step the state machine at +0x16C. State 0 drives the effect envelope and
// the target search; state 1 plays the first path leg; state 2 the blended middle leg with the release/restart handling;
// state 3 the return leg, after which the timer is reloaded and the tracker reset.
typedef int qword __attribute__((mode(TI)));
struct Rows { qword row[3]; };
extern struct { float t; float dt; } D_0036BB98;
struct Follower {
    unsigned char pad00[0x150]; void *effect;
    unsigned char pad154[0x168 - 0x154]; int link;
    int state;
    unsigned char pad170[0x17C - 0x170]; float timer;
    qword start; qword finish;
    unsigned char pad1A0[0x1D0 - 0x1A0]; Rows basis;
    qword up;
    unsigned char pad210[0x280 - 0x210]; float f280;
    unsigned char pad284[0x288 - 0x284]; float f288;
    unsigned char pad28C[0x294 - 0x28C]; float f294, f298;
    unsigned char pad29C[0x2AC - 0x29C]; float f2AC;
};
extern "C" void func_0023C660(Follower *self);
extern "C" void func_00233528(Follower *self);
extern "C" void func_00232CE0(Follower *self);
extern "C" void func_00233188(Follower *self, float first, float second);
extern "C" void func_00232F60(Follower *self);
extern "C" void func_00137588(void *effect, Follower *self, float a, float b, int kind, int *link);
extern "C" int func_002336B0(Follower *self);
extern "C" void func_00233280(Follower *self, float time, qword *start, qword *finish);
extern "C" void func_00233360(Follower *self, float time, float first, float second, Rows *rows, qword *up);
extern "C" void func_00233098(Follower *self);
extern "C" void func_00232A38(Follower *self, int mode);
extern "C" void func_00232478(Follower *self)
{
    func_0023C660(self);
    switch (self->state) {
    case 0:
        func_00233528(self);
        func_00232CE0(self);
        break;
    case 1:
        func_00233188(self, self->f280, 0.0f);
        if (self->timer <= 0.0f)
            func_00232F60(self);
        break;
    case 2:
        if (0.5f <= self->timer) {
            if (self->timer - D_0036BB98.dt < 0.5f) {
                func_00137588(self->effect, self, 0.0f, 1.0f, 1, &self->link);
            } else if (func_002336B0(self)) {
                func_00137588(self->effect, self, 0.0f, 1.0f, 1, &self->link);
                func_00233280(self, 0.5f, &self->start, &self->finish);
                func_00233360(self, 0.5f, self->f288, 0.0f, &self->basis, &self->up);
                self->timer = 0.5f;
            }
        }
        func_00233188(self, self->f288, 0.0f);
        if (self->timer <= 0.0f)
            func_00233098(self);
        break;
    case 3:
        func_00233188(self, self->f294, self->f298);
        if (self->timer <= 0.0f) {
            self->timer = self->f2AC;
            func_00232A38(self, 0);
        }
        break;
    }
}
