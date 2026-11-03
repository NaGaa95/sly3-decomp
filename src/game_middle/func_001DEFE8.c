// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31
// Actor event handler: kind 10 reacts to animation-script events of the current clip or resource (grab, hit and
// state-entry markers), kind 11 reacts to the state-6 timing markers. Sly 2 relatives: the func_001B5xxx handlers.
// Allocation note (event 0x185): the method pointer and `this` of the second Matrix call are read before the home
// qword is stored, so the stack store sorts after those loads (it lands in the jalr delay slot).
typedef int qword __attribute__((mode(TI)));
struct Method { short adjustment, reserved; void *function; };
struct Frame { qword row[4]; };
struct Object { unsigned char prefix[0xC]; struct Method *methods; };
struct Event { void *source; int detail; int id; };
struct Held { unsigned char prefix[0x190]; void *grabbed; };
struct Target { unsigned char prefix[0x1F0]; int active; };
struct Actor {
    unsigned char prefix0[0xC];
    struct Method *methods;
    unsigned char gap10[0x113C - 0x10];
    void *clip;
    void *clipEnd;
    unsigned char gap1144[0x1520 - 0x1144];
    int state;
    unsigned char gap1524[0x1540 - 0x1524];
    struct Held *held;
    unsigned char gap1544[0x1584 - 0x1544];
    int x1584;
    unsigned char gap1588[4];
    int x158C;
    unsigned char gap1590[0x1668 - 0x1590];
    float x1668, x166C;
    int x1670;
    unsigned char gap1674[4];
    int index1678;
    unsigned char gap167C[0x1898 - 0x167C];
    int x1898, x189C, x18A0;
    unsigned char gap18A4[0x18DC - 0x18A4];
    void *resource;
    unsigned char gap18E0[4];
    int x18E4;
    unsigned char gap18E8[0x19A8 - 0x18E8];
    int x19A8;
    unsigned char gap19AC[0x1C90 - 0x19AC];
    struct Target *x1C90;
};
extern char D_00475480[];
extern float D_00324658[];
int func_00153738(struct Actor *self, int kind, struct Event *event);
void func_001DF600(struct Actor *self, int state);
void func_001DE690(struct Actor *self, int state);
void func_001E1EB8(struct Actor *self, int mode);
void func_001E0160(struct Actor *self);
void func_001E0420(struct Actor *self);
void func_002730D8(void *context);
void func_00173E00(void *world, int first, qword position, void *actor);
int func_0013B500(void *object, int key);
void func_00156DC0(struct Actor *self, qword target, int flags);
void func_0020F508(struct Target *target);
static inline qword ScalarBits(float f)
{
    qword r;
    __asm__("mfc1 %0,%1" : "=r,j"(r) : "f,f"(f), "i,r"(0));
    return r;
}
static inline qword AddScaled(qword base, qword direction, qword scale)
{
    qword r;
    __asm__("vadda.xyzw $ACC,%1,$vf0
	vmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(base), "j"(direction), "j"(scale));
    return r;
}
static inline struct Frame *Matrix(struct Actor *self)
{
    struct Method *method = &self->methods[36];
    return ((struct Frame *(*)(void *))method->function)((char *)self + method->adjustment);
}
void func_001DEFE8(struct Actor *self, int kind, struct Event *event)
{
    union { qword q; float f[4]; } home;
    func_00153738(self, kind, event);
    switch (kind) {
    case 10:
        if (event->source != self->clip && event->source != self->resource)
            return;
        switch (event->id) {
        case 0x1C5:
            func_001DF600(self, 1);
            break;
        case 0x1C6:
            func_00173E00(D_00475480, 0, Matrix(self)->row[3], self);
            break;
        case 0x219:
            switch (self->state) {
            case 7:
                func_001E0160(self);
                break;
            case 8:
                func_001E0420(self);
                break;
            case 16:
                func_002730D8((char *)self + 0x18E0);
                break;
            }
            break;
        case 0x1F4:
            self->x1584 = 1;
            break;
        case 0x1F6:
            if (self->x158C)
                break;
            func_00173E00(D_00475480, 0, Matrix(self)->row[3], self);
            func_001E1EB8(self, 1);
            break;
        case 0x1F5:
            if (self->x158C == 1)
                func_001E1EB8(self, 2);
            break;
        case 0x185:
            if (self->held) {
                if (func_0013B500(self->held->grabbed, 0x3A)) {
                    qword position = Matrix(self)->row[3];
                    qword scale = ScalarBits(450.0f);
                    struct Method *method = &self->methods[36];
                    struct Frame *(*fn)(void *) = (struct Frame *(*)(void *))method->function;
                    void *target = (char *)self + method->adjustment;
                    home.q = scale;
                    func_00156DC0(self, AddScaled(position, fn(target)->row[0], scale), 0);
                }
            }
            break;
        case 0x21A:
            if (self->x18E4 == 3)
                self->x19A8 = 1;
            break;
        case 0x2A0:
            self->x1898 = 1;
            break;
        case 0x2A1:
            self->x189C = 1;
            break;
        case 0x2A2:
            self->x18A0 = 1;
            break;
        case 0x247:
            if (self->x1C90)
                self->x1C90->active = 1;
            break;
        case 0x248:
            if (self->x1C90)
                func_0020F508(self->x1C90);
            break;
        }
        break;
    case 11:
        if (event->source != self->clipEnd)
            return;
        if (self->state != 6)
            return;
        if (event->id == event->detail)
            return;
        switch (event->id) {
        case 0x1F8:
        case 0x1FE:
            func_001DE690(self, 0);
            break;
        case 0x1F9:
        case 0x1FA:
        case 0x1FB:
        case 0x1FC:
        case 0x1FD: {
            float value = D_00324658[self->index1678];
            self->x166C = value;
            self->x1668 = value;
            self->x1670 = (int)(value * 4.0f);
            break;
        }
        }
        break;
    }
}
