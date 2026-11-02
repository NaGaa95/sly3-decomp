// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct M4 { qword r[4]; };
struct M3 { qword r[3]; };
struct VTE { short delta, pad; void *fn; };
struct JOB;
struct SPACE;
struct CHANNEL { char pad0[0x90]; JOB *current; char pad94[0xC]; SPACE *space; int wordA4; float endTime; };
struct MOTION;
struct ANIM { char pad0[0x14]; MOTION *motion; int w18; float start; char pad20[0x20]; float duration; };
struct FOLLOW { char pad0[0x80]; qword velocity; };
struct OWNER {
    char pad0[0xC]; VTE *vt; char pad10[0x40]; SPACE *space;
    char pad54[0x1C0 - 0x54]; M3 basis;
    char pad1F0[0x113C - 0x1F0]; ANIM *playing;
};
struct OBJ {
    char pad0[0xC]; VTE *vt; char pad10[0x38]; CHANNEL *position; CHANNEL *orientation;
    char pad50[0xD8 - 0x50]; FOLLOW *follow;
};
struct SOURCE { char pad0[0xC]; VTE *vt; };
struct SELF {
    OWNER *owner; char pad4[0x30]; SOURCE *source; char pad38[0x5C];
    JOB *positionJob; JOB *otherJob; JOB *orientationJob;
};
struct CLOCK { float time, dt; };
extern CLOCK D_0036BB98;
extern qword D_003258A0;
extern "C" {
void func_001309D8(JOB **);
float func_001368E0(MOTION *, int);
void func_00137070(MOTION *, OWNER *, float, float, SPACE *, SPACE *, M4 *, int);
void func_002BA818(qword *, qword);
void func_0011D558(M4 *, const M4 *, const M4 *);
OBJ *func_00208AA0(OWNER *, OBJ *);
M4 func_001C9708(int, OBJ *, M4 *);
M4 func_0011D768(M4 *);
void func_001C7A00(OBJ *, int, int);
float func_001B83F0(qword, qword, float, float, float, float);
void func_00138B68(ANIM *, float);
qword func_0028E910(int, SPACE *, qword);
qword func_0028E990(int, SPACE *, qword);
JOB *func_00130348(OBJ *, CHANNEL *, int, float, qword, qword);
M3 func_0028EA00(int, SPACE *, M3 *);
qword func_0011D3C0(M3 *);
JOB *func_00130078(OBJ *, CHANNEL *, int, int, int, qword);
void func_0023FC90(OBJ *, int);
int func_0013B500(OBJ *, int);
}
struct VU_FLOAT {
    qword q;
    VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); }
};
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword MulAdd(qword a, VU_FLOAT sa, qword b, VU_FLOAT sb)
{
    qword r;
    __asm__("vmulax.xyzw $ACC, %2, %1x\n\t"
            "vmaddx.xyzw %0, %3, %4x" : "=j"(r) : "j"(sa.q), "j"(a), "j"(b), "j"(sb.q));
    return r;
}
static inline SPACE *SourceMatrix(SOURCE *p, M4 *out)
{
    VTE &v = p->vt[37];
    return ((SPACE *(*)(void *, M4 *))v.fn)((char *)p + v.delta, out);
}
static inline M4 *WorldMatrix(void *p, VTE *vt)
{
    VTE &v = vt[36];
    return ((M4 * (*)(void *))v.fn)((char *)p + v.delta);
}
static inline float Max(float a, float b) { return a < b ? b : a; }
extern "C" void func_00208D50(SELF *self, OBJ *obj)
{
    M4 original, sample, start, final;
    qword velocity, destination, delta, endVelocity;
    func_001309D8(&self->positionJob);
    float zero = 0.0f;
    func_001309D8(&self->otherJob);
    func_001309D8(&self->orientationJob);
    ANIM *anim = self->owner->playing;
    MOTION *motion = anim->motion;
    float time = func_001368E0(motion, 0x1F5);
    float phase = (time - anim->start) / anim->duration;
    SPACE *space = SourceMatrix(self->source, &original);
    M4 *psample = &sample;
    func_00137070(motion, self->owner, time, zero, space, self->owner->space, psample, 0);
    OWNER *owner = self->owner;
    M4 *pstart = &start;
    M3 *basis = &owner->basis;
    {
        M4 *pm = WorldMatrix(owner, owner->vt);
        func_002BA818(&start.r[3], pm->r[3]);
    }
    *(M3 *)pstart = *basis;
    ((float *)&start)[11] = zero;
    ((float *)&start)[7] = zero;
    ((float *)&start)[3] = zero;
    ((float *)pstart)[15] = 1.0f;
    {
    M4 intermediate;
    M4 *pinter = &intermediate;
    {
        M4 product;
        func_0011D558(&product, pstart, psample);
        func_0011D558(pinter, &product, &original);
        final = intermediate;
    }
    OBJ *counter = func_00208AA0(self->owner, obj);
    if (counter) {
        M4 *cm = WorldMatrix(counter, counter->vt);
        M4 product = func_001C9708(0, obj, cm);
        intermediate = product;
        M4 *pfinal = &final;
        M4 inverse = func_0011D768(pinter);
        func_0011D558(&product, pfinal, &inverse);
        final = product;
    }
    }
    func_001C7A00(obj, 0, 15);
    const qword *pv = obj->follow ? &obj->follow->velocity : &D_003258A0;
    velocity = *pv;
    destination = final.r[3];
    delta = Sub(destination, WorldMatrix(obj, obj->vt)->r[3]);
    float unit = 1.0f;
    float duration = Max(phase, func_001B83F0(delta, velocity, 400.0f, -400.0f, unit, -1.0f));
    func_00138B68(anim, phase / duration);
    phase = duration;
    float inv = unit / phase;
    float neg = phase * -0.5f, pos = phase * 0.5f;
    qword first = MulAdd(delta, VU_FLOAT(inv), velocity, VU_FLOAT(neg));
    endVelocity = MulAdd(delta, VU_FLOAT(inv), velocity, VU_FLOAT(pos));
    {
        VTE &v = obj->vt[40];
        ((void (*)(void *, qword))v.fn)((char *)obj + v.delta, first);
    }
    float endTime = D_0036BB98.time + phase;
    qword position = func_0028E910(0, obj->position->space, final.r[3]);
    qword endVel = func_0028E990(0, obj->position->space, endVelocity);
    self->positionJob = func_00130348(obj, obj->position, 5, endTime, position, endVel);
    M3 angles;
    angles = func_0028EA00(0, obj->orientation->space, (M3 *)&final);
    qword anglesQ = func_0011D3C0(&angles);
    JOB *job = func_00130078(obj, obj->orientation, 5, 10, 2, anglesQ);
    self->orientationJob = job;
    if (obj->orientation->current == job)
        obj->orientation->endTime = endTime;
    func_0023FC90(obj, 1);
    if (func_0013B500(obj, 0x66)) {
        VTE &v = obj->vt[80];
        ((void (*)(void *, int))v.fn)((char *)obj + v.delta, 5);
    }
}
