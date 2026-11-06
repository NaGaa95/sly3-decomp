// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_001BDBB0: set the state of a look-around mode (Sly 2 JTMODE::SetState relative, func_0019CD38).
typedef int qword __attribute__((mode(TI)));
struct VTE { short delta, pad; void *fn; };
struct CLIP;
struct ANIM;
struct CAM_A { char pad0[0x24]; float heading; };
struct CAM_B { char pad0[0xB4]; float heading; };
struct ACTOR {
    char pad0[0xC]; VTE *vt; char pad10[0x130 - 0x10]; int x130; char pad134[0x1A0 - 0x134]; float acceleration[3];
};
struct LOOK { qword position; qword direction; float amount; char pad24[0xC]; int x30; int x34; };
struct JTMODE {
    ACTOR *actor; int state; float tEnter; CLIP *start; CLIP *end; ANIM *anim; int kind;
    char hud[0x40 - 0x1C]; ACTOR *other; void *hudOverride; char pad48[8]; LOOK look;
    char pad90[0xA4 - 0x90]; CAM_A *camA; CAM_B *camB;
};
struct CLOCK { float t, dt; };

extern "C" {
extern CLOCK g_clock;
extern qword D_00317560;
extern char D_00474FF0[];
extern char D_00475480[];
void *func_001F4A80(ACTOR *);
void func_00169C40(void *);
void func_00166548(void *);
void func_001BE4A8(JTMODE *);
void func_00156928(ACTOR *);
void func_00156900(ACTOR *);
void func_00248A78(void *, int, float, int);
void func_00242228(ACTOR *);
void func_00241FC0(ACTOR *);
void func_001A93C8(void *, int, int);
void func_001A94A8(void *, int);
void func_001A9420(void *, int, int);
void func_001A94F0(void *, int);
void *func_00169BF8(int);
CAM_A *func_00169F60(void *, void *, int, ACTOR *);
CAM_B *func_0016A6F0(void *, void *, int);
void func_00169CE0(void *);
int func_0011E9F0(float, float, float);
void func_0016AE40(CAM_B *, qword, qword, float);
void func_0016ADC0(CAM_B *, int);
void func_0016AE00(CAM_B *, int);
void func_0016AE90(CAM_B *);
void func_001BECB8(void *, void *);
void func_001BE5A8(void *, int);
void func_001BE408(JTMODE *);
void func_00137588(CLIP *, ACTOR *, float, float, int, ANIM **);
void func_0024E878(ACTOR *, float);
}

static inline void Action(ACTOR *p, int slot, int a, int b)
{
    VTE &v = p->vt[slot];
    ((void (*)(void *, int, int))v.fn)((char *)p + v.delta, a, b);
}
static inline int Query(ACTOR *p)
{
    VTE &v = p->vt[104];
    return ((int (*)(void *))v.fn)((char *)p + v.delta);
}
static inline void SetVector(ACTOR *p, int slot, qword q)
{
    VTE &v = p->vt[slot];
    ((void (*)(void *, qword))v.fn)((char *)p + v.delta, q);
}
static inline float GetX(qword q) { float f; __asm__("mtc1 %1,%0" : "=f"(f) : "r"(q)); return f; }
static inline float GetY(qword q) { float f; __asm__("prot3w %0,%1" : "=r"(f) : "r"(q)); return f; }
static inline float GetZ(qword q) { float f; __asm__("pextuw %0,$zero,%1" : "=r"(f) : "r"(q)); return f; }
static inline int Equal(qword a, qword b)
{
    return func_0011E9F0(GetX(a), GetX(b), 0.0001f) && func_0011E9F0(GetY(a), GetY(b), 0.0001f) && func_0011E9F0(GetZ(a), GetZ(b), 0.0001f);
}

extern "C" void func_001BDBB0(JTMODE *p, int state)
{
    CLIP *clip;
    if (state == p->state)
        return;

    switch (p->state) {
    case 1: {
        void *target = func_001F4A80(p->actor);
        func_00169C40(&p->camA);
        func_00169C40(&p->camB);
        if (target)
            func_00166548(target);
        if (p->kind == 1) {
            func_001BE4A8(p);
            Action(p->actor, 95, 0x3F, 0);
            func_00156928(p->actor);
        }
        func_00248A78(D_00474FF0, 0, 1.0f, 3);
        func_00248A78(D_00474FF0, 1, 1.0f, 3);
        if (p->kind != 2)
            func_00242228(p->actor);
        p->state = state;
        break;
    }
    case -1:
        if (p->kind == 1) {
            func_001A93C8(D_00475480, p->actor->x130, 2);
            func_001A94A8(D_00475480, p->actor->x130);
        }
        p->state = state;
        break;
    default:
        p->state = state;
        break;
    }
    p->tEnter = g_clock.t;
    clip = 0;
    switch (state) {
    case 0:
        clip = p->start;
        break;
    case 1: {
        void *target = func_001F4A80(p->actor);
        switch (p->kind) {
        case 0: {
            CAM_A *cam = func_00169F60(func_00169BF8(0x60), target, 3, p->actor);
            p->camA = cam;
            func_00169CE0(cam);
            func_0024E878(p->actor, p->camA->heading);
            func_001BE5A8(p->hud, 0);
            break;
        }
        case 1: {
            CAM_B *cam = func_0016A6F0(func_00169BF8(0xE0), target, 3);
            LOOK *look = &p->look;
            int zeroPos;
            int fresh = 0;
            p->camB = cam;
            func_00169CE0(cam);
            zeroPos = Equal(D_00317560, look->position);
            if (!zeroPos) {
                int zeroDir = Equal(D_00317560, look->direction);
                if (!zeroDir && look->amount != 0.0f)
                    fresh = 1;
            }
            if (fresh)
                func_0016AE40(p->camB, look->position, look->direction, look->amount);
            func_0024E878(p->actor, p->camB->heading);
            func_001BE408(p);
            if (look->x30) {
                func_0016ADC0(p->camB, look->x30);
                func_0016AE90(p->camB);
            }
            if (look->x34) {
                func_0016AE00(p->camB, look->x34);
                func_0016AE90(p->camB);
            }
            func_001BECB8(p->hud, p->hudOverride);
            func_001BE5A8(p->hud, 0);
            Action(p->actor, 94, 0x3F, 0);
            func_00156900(p->actor);
            break;
        }
        case 2:
            if (target) {
                CAM_A *cam = func_00169F60(func_00169BF8(0x60), target, 3, p->other);
                p->camA = cam;
                func_00169CE0(cam);
            }
            func_001BE5A8(p->hud, 0);
            break;
        }
        ACTOR *actor = p->actor;
        float *acceleration = actor->acceleration;
        acceleration[2] = 0.0f;
        acceleration[1] = 0.0f;
        acceleration[0] = 0.0f;
        SetVector(p->actor, 40, D_00317560);
        SetVector(p->actor, 41, D_00317560);
        if (target)
            func_00166548(target);
        func_00248A78(D_00474FF0, 0, 0.6f, 3);
        func_00248A78(D_00474FF0, 1, 0.6f, 3);
        if (p->kind != 2)
            func_00241FC0(p->actor);
        break;
    }
    case 2:
        func_001BE5A8(p->hud, 5);
        clip = p->end;
        break;
    case -1:
        switch (p->kind) {
        case 0:
        case 2:
            func_001BE5A8(p->hud, -1);
            break;
        case 1:
            func_001BE5A8(p->hud, -1);
            func_001A9420(D_00475480, p->actor->x130, 2);
            func_001A94F0(D_00475480, p->actor->x130);
            break;
        }
        p->kind = -1;
        break;
    }
    if (clip && !Query(p->actor))
        clip = 0;
    func_00137588(clip, p->actor, 0.0f, 1.0f, 1, &p->anim);
}
