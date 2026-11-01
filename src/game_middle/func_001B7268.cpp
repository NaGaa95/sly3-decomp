// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_001B7268: enter a movement state of the hero's action context.
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
struct VTE { short delta, pad; void *fn; };
struct M4 { U r[4]; };
struct JOY { float x, y, amount; };
struct ACTOR {
    char pad0[0xC]; VTE *vt; char pad10[0x134 - 0x10]; JOY *pjoy; char pad138[0x1BC - 0x138]; float heading;
    char pad1C0[0x290 - 0x1C0]; float x290; char pad294[0x110C - 0x294]; float stick; char pad1110[0x1408 - 0x1110];
    float x1408; char pad140C[0x19F0 - 0x140C]; int x19F0;
};
struct CONTEXT {
    ACTOR *actor; int state; int arg; char padC[0x18 - 0xC]; float x18; char pad1C[0x24 - 0x1C]; int x24; int x28; char pad2C[4];
    float x30; float x34; float x38; int x3C; float x40; float x44; float x48; char pad4C[0x60 - 0x4C]; float x60; float x64; float x68;
    char pad6C[0x118 - 0x6C]; ACTOR *rider; char pad11C[0x120 - 0x11C]; qword riderScale; char pad130[0x130 - 0x130];
    float x130; void *x134; char pad138[0x13C - 0x138]; int x13C; char pad140[0x190 - 0x140]; int x190;
};
struct CLOCK { float t, dt; };

extern "C" {
extern CLOCK g_clock;
extern qword D_00317560;
extern float D_003457A0;
qword func_001BB4E8(CONTEXT *, int);
void func_0024F1E8(ACTOR *, float);
void func_001B77F8(CONTEXT *, int, int);
qword func_0011FD70(float, float, float);
void func_00120B00(qword, float *, float *, int);
void func_001F47C8(ACTOR *, void *);
float func_002A3EE8(float, float);
int func_0013B500(ACTOR *, int);
}

static inline qword Velocity(ACTOR *p) { VTE &v = p->vt[38]; return ((qword (*)(void *))v.fn)((char *)p + v.delta); }
static inline M4 *Matrix(ACTOR *p) { VTE &v = p->vt[36]; return ((M4 *(*)(void *))v.fn)((char *)p + v.delta); }
static inline void SetVelocity(ACTOR *p, qword q) { VTE &v = p->vt[40]; ((void (*)(void *, qword))v.fn)((char *)p + v.delta, q); }
static inline void Enter(ACTOR *p, int arg) { VTE &v = p->vt[99]; ((void (*)(void *, int))v.fn)((char *)p + v.delta, arg); }
static inline qword Mul(qword a, qword b) { qword r; __asm__("vmul.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Add(qword a, qword b) { qword r; __asm__("vadd.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline float GetZ(qword q) { float f; __asm__("pextuw %0,$0,%1" : "=r"(f) : "r"(q)); return f; }

extern "C" void func_001B7268(CONTEXT *self, int state, int arg, int arg3, float scale)
{
    if (state != 6)
        self->state = state;
    self->arg = arg;
    Enter(self->actor, 1);
    if (state != 6) {
        self->x3C = 0;
        float t = g_clock.t;
        self->x40 = self->x44 = self->x48 = t;
    }
    if (state == 9) {
        self->x130 = self->actor->x290;
        func_0024F1E8(self->actor, 0.75f);
    }
    U q;
    q.q = func_001BB4E8(self, state);
    q.f[2] *= scale;
    qword extra;
    if (self->rider) {
        qword factor = self->riderScale;
        extra = Mul(factor, Velocity(self->rider));
    } else
        extra = D_00317560;
    q.f[2] += GetZ(extra);
    SetVelocity(self->actor, q.q);
    self->actor->x1408 = g_clock.t;
    if (state != 6)
        self->x18 = g_clock.t;

    switch (state) {
    case 0:
        func_001B77F8(self, 6, arg3);
        self->x24 = 0;
        self->x28 = 0;
        self->x30 = 1.0f;
        self->x34 = 1.0f;
        break;
    case 11:
        func_001B77F8(self, 6, arg3);
        self->x24 = 1;
        self->x28 = self->x190;
        self->x30 = 1.0f;
        self->x34 = 1.0f;
        break;
    case 3:
        if (self->actor->pjoy->amount < 0.2f) {
            self->x3C = 3;
            qword old = q.q;
            q.q = Add(old, func_0011FD70(self->actor->heading, 100.0f, 0.0f));
            SetVelocity(self->actor, q.q);
        }
        func_001B77F8(self, 0, arg3);
        self->x30 = 1.0f;
        self->x34 = 0.6f;
        self->x24 = 0;
        self->x28 = 0;
        break;
    case 1:
    case 2:
    case 18:
        func_001B77F8(self, 0, arg3);
        self->x24 = 0;
        self->x28 = 0;
        self->x30 = 1.0f;
        self->x34 = 1.0f;
        break;
    case 16:
        func_001B77F8(self, 0, arg3);
        self->x24 = 0;
        self->x28 = 0;
        self->x30 = 1.0f;
        self->x34 = 1.0f;
        break;
    case 9:
        func_001B77F8(self, 0, arg3);
        self->x24 = 0;
        self->x28 = 0;
        func_001F47C8(self->actor, self->x134);
        self->x34 = 1.5f;
        self->x30 = 1.2f;
        self->x13C = 1;
        break;
    case 7:
        func_001B77F8(self, 9, arg3);
        self->x24 = 0;
        self->x28 = 0;
        self->x34 = 1.0f;
        self->x30 = 1.0f;
        break;
    case 8: {
        float one = 1.0f;
        func_001B77F8(self, 7, arg3);
        self->x24 = 0;
        self->x28 = 0;
        self->x30 = one;
        self->x34 = one;
        func_00120B00(q.q, &self->x60, &self->x68, 0);
        self->x64 = one;
        break;
    }
    case 6:
        self->x28++;
        func_001B77F8(self, self->state == 13 ? 3 : 2, arg3);
        break;
    case 13: {
        func_001B77F8(self, 1, arg3);
        self->x34 = 1.75f;
        self->x30 = 1.0f;
        self->x24 = 0;
        self->x28 = 0;
        ACTOR *actor = self->actor;
        float heading;
        if (0.2f < actor->pjoy->amount)
            heading = actor->stick;
        else {
            M4 *m = Matrix(actor);
            heading = func_002A3EE8(m->r[0].f[1], m->r[0].f[0]);
        }
        self->x3C = 3;
        q.q = func_0011FD70(heading, D_003457A0 * self->x34, q.f[2]);
        SetVelocity(self->actor, q.q);
        break;
    }
    case 10:
        self->x3C = -1;
        func_001B77F8(self, 0x16, arg3);
        self->x24 = 0;
        self->x28 = self->x190;
        self->x30 = 0.0f;
        self->x34 = 0.0f;
        break;
    case 12:
        func_001B77F8(self, 1, arg3);
        self->x3C = 3;
        self->x24 = 0;
        self->x28 = 0;
        self->x30 = 1.0f;
        self->x34 = 1.0f;
        break;
    case 15:
        func_001B77F8(self, 6, arg3);
        self->x24 = 0;
        self->x28 = self->x190;
        self->x30 = 1.0f;
        self->x34 = 1.0f;
        break;
    case 14:
    case 17:
        func_001B77F8(self, 0, arg3);
        self->x24 = 0;
        self->x28 = self->x190;
        self->x30 = 1.0f;
        self->x34 = 1.0f;
        break;
    }
    if (state != 6) {
        if (func_0013B500(self->actor, 0x34))
            self->actor->x19F0 = -1;
        self->x38 = GetZ(Matrix(self->actor)->r[3].q);
    }
}
