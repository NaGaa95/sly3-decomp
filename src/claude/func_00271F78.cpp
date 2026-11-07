// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// SLY3_ASFIX: engine-divfix1
// func_00271F78: the JTTHROW update (Sly 2 func_0021F418). In the throw states (4..6) the aim point follows the
// stick (planar polar update clamped to lmAim * 1.5) or blends between two points, then the arc is predicted
// (func_00272628); the state machine (func_002734E8 = set state) runs until the state settles; while the hero moves
// along an animation its direction gets the animation track's height.
// Matching notes: the hero position is a plain qword (its reload spill slot is the 0x30 home), the stick vector a
// qword live across func_0011FD70 (its vf caller-save slot is 0x40), and the VU angle temporaries go to w.scratch.
typedef int qword __attribute__((mode(TI)));
union V { qword q; float f[4]; int n[4]; };
struct RANGE { float lo, hi; };
struct M4 { V r[4]; };
struct VE { short delta, pad; void *pfn; };
#define VF1(n) virtual void V##n();
class LO {
public:
    int hdr[3];
    VF1(1) VF1(2) VF1(3) VF1(4) VF1(5) VF1(6) VF1(7) VF1(8) VF1(9) VF1(10) VF1(11) VF1(12) VF1(13) VF1(14) VF1(15) VF1(16)
    VF1(17) VF1(18) VF1(19) VF1(20) VF1(21) VF1(22) VF1(23) VF1(24) VF1(25) VF1(26) VF1(27) VF1(28) VF1(29) VF1(30) VF1(31) VF1(32)
    VF1(33) VF1(34) VF1(35)
    virtual M4 *Matrix();                       // 36
    VF1(37) VF1(38) VF1(39) VF1(40) VF1(41) VF1(42) VF1(43) VF1(44) VF1(45) VF1(46) VF1(47) VF1(48)
    VF1(49) VF1(50) VF1(51) VF1(52) VF1(53) VF1(54) VF1(55) VF1(56) VF1(57) VF1(58) VF1(59) VF1(60) VF1(61) VF1(62) VF1(63) VF1(64)
    VF1(65) VF1(66) VF1(67) VF1(68) VF1(69) VF1(70) VF1(71) VF1(72) VF1(73) VF1(74) VF1(75) VF1(76) VF1(77) VF1(78) VF1(79) VF1(80)
    VF1(81) VF1(82) VF1(83) VF1(84) VF1(85) VF1(86) VF1(87) VF1(88) VF1(89) VF1(90) VF1(91) VF1(92) VF1(93) VF1(94) VF1(95) VF1(96)
    VF1(97) VF1(98)
    virtual void SetCarry(int);                 // 99
};
struct ASEG;
struct TRACK { VE *vt; };
struct TRACKREF { int tag; TRACK *track; };
struct ASEGA { char pad0[0x14]; ASEG *definition; char pad18[4]; float time; char pad20[0x20]; float scale; };
struct CONTROL { char pad0[8]; float speed; };
struct HERO : LO { char pad10[0x124]; CONTROL *control; char pad138[0x80]; int movement; char pad1BC[0x34]; V direction;
                   char pad200[0xF0C]; float heading; char pad1110[0x2C]; ASEGA *animation; };
struct SEL : LO { char pad10[0x128]; int sentinel; };
struct PLAYER : LO { char pad10[0x1510]; int mode; };
struct GAMESTATE { char pad0[0x19E0]; int mode; };
struct S {
    HERO *owner; int state; char pad8[8]; SEL *selected; float idleThreshold, activeThreshold; RANGE bounds; float radius, scale;
    char pad2C[0x14]; float blend0; char pad44[8]; float blend1; char pad50[8]; ASEG *animation0; char pad5C[0x6C]; int fCarry;
    char padCC[0x24]; V targetWorld; V pad100; V transitionBegin, transitionEnd; float transitionStart, transitionDuration;
    int transitioning; int fAimFixed;
};
struct CLOCK { float t, dt; };
struct WORK { V scratch; V delta; float angle, radius; int pad28[2]; };
extern CLOCK g_clock;
extern PLAYER *D_0036B250;
extern GAMESTATE *D_00370AC0;
extern V D_00317560;
extern "C" {
void func_00272628(S *, int);
void func_002734E8(S *, int);
void func_00273278(S *);
int func_00138AC8(ASEGA *);
int func_001A7A80(CONTROL *, int, float);
int func_0013B500(LO *, int);
TRACKREF *func_00136EE0(ASEG *, HERO *, int, int);
qword func_0011FD70(float, float, float);
void func_00120B00(qword, float *, float *, float *);
float func_0011EE68(RANGE *, float);
float func_001205C8(qword);
float func_002A3EE8(float, float);
float func_0011E3B8(float);
void func_00148938(ASEG *);
}
static inline qword Q(float f) { qword r; __asm__("qmtc2.ni %1,%0" : "=j"(r) : "r"(f)); return r; }
static inline qword Combine(qword a, qword b, qword g0, qword g1)
{ qword r; __asm__("vmulax.xyzw ACC,%1,%2x\n\tvmaddx.xyzw %0,%3,%4x" : "=j"(r) : "j"(a), "j"(g0), "j"(b), "j"(g1)); return r; }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Add(qword a, qword b) { qword r; __asm__("vadd.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline float AngleTo(S *s, V &home, qword pos, qword origin)
{
    home.q = Sub(pos, origin);
    float heading = func_001205C8(home.q);
    M4 *m = s->owner->Matrix();
    return func_0011E3B8(heading - func_002A3EE8(m->r[0].f[1], m->r[0].f[0]));
}
typedef void (*EVAL)(void *, int, V *, float, float);

extern "C" void func_00271F78(S *s)
{
    WORK w;
    CONTROL *control = s->owner->control;
    qword posOwner = s->owner->Matrix()->r[3].q;
    int state = s->state;
    if (state < 7) {
    if (state >= 4) {
        if (s->transitioning) {
            float begin = s->transitionStart, end = begin + s->transitionDuration, time = g_clock.t;
            if (end <= time) {
                s->transitioning = 0;
                s->targetWorld.q = s->transitionEnd.q;
            } else {
                float u = (time - begin) / (end - begin);
                qword qa = Q(1.0f - u);
                w.scratch.q = qa;
                qword qb = Q(u);
                s->targetWorld.q = Combine(s->transitionBegin.q, s->transitionEnd.q, qa, qb);
                w.scratch.q = qb;
            }
        } else if (!s->fAimFixed) {
            *(RANGE *)&w.scratch = s->bounds;
            ((RANGE *)&w.scratch)->hi *= 1.5f;
            w.delta.q = Sub(s->targetWorld.q, posOwner);
            w.delta.f[2] = 0.0f;
            float speed = control->speed * g_clock.dt * s->scale;
            float elevation = w.delta.f[2];
            qword vec = w.delta.q;
            qword movement = func_0011FD70(s->owner->heading, speed, elevation);
            w.delta.q = Add(vec, movement);
            func_00120B00(w.delta.q, &w.angle, &w.radius, 0);
            w.radius = func_0011EE68((RANGE *)&w.scratch, w.radius);
            qword polar = func_0011FD70(w.angle, w.radius, elevation);
            s->targetWorld.q = Add(posOwner, polar);
            w.delta.q = polar;
        }
        func_00272628(s, 1);
    }
    }
    for (;;) {
        int previous = s->state;
        ASEGA *animation = s->owner->animation;
        switch (previous) {
        case 0: {
            float angle = AngleTo(s, w.scratch, s->selected->Matrix()->r[3].q, posOwner);
            float threshold = s->idleThreshold;
            if (threshold < angle)
                func_002734E8(s, 2);
            else if (angle < -threshold)
                func_002734E8(s, 1);
            else {
                s->blend1 = angle / threshold * 0.5f + 0.5f;
                s->blend0 = 1.0f - s->blend1;
                func_00148938(s->animation0);
            }
            break;
        }
        case 1: case 2:
            if (!animation || func_00138AC8(animation))
                func_002734E8(s, 0);
            break;
        case 3:
            if (animation && !func_00138AC8(animation)) {
                if (!s->fCarry)
                    break;
                if (!func_001A7A80(control, 0x40, 0.25f))
                    break;
            }
            if ((LO *)s->selected == (LO *)D_0036B250) {
                if (D_0036B250->mode == 10)
                    func_002734E8(s, 4);
                else
                    func_002734E8(s, 0);
            } else if (animation && !func_00138AC8(animation) && D_00370AC0->mode == 20) {
                func_002734E8(s, 7);
            } else {
                func_00273278(s);
                func_002734E8(s, 0);
            }
            break;
        case 4: case 5: case 6: {
            if (func_0013B500(s->selected, 0x71) && s->selected->sentinel != -1) {
                s->owner->SetCarry(0);
                break;
            }
            float margin = 0.1f;
            if (func_001A7A80(control, 0xC0, margin)) {
                func_002734E8(s, 7);
                break;
            }
            if (func_001A7A80(control, 0x30, margin)) {
                func_00273278(s);
                if (s->animation0)
                    func_002734E8(s, 0);
                else
                    s->owner->SetCarry(0);
                return;
            }
            if (!animation || func_00138AC8(animation))
                func_002734E8(s, 4);
            else if (s->state == 4) {
                float angle = AngleTo(s, w.scratch, s->targetWorld.q, posOwner);
                float threshold = s->activeThreshold;
                if (threshold < angle)
                    func_002734E8(s, 6);
                else if (angle < -threshold)
                    func_002734E8(s, 5);
            }
            break;
        }
        case 7:
            if (!animation || func_00138AC8(animation)) {
                if (s->animation0)
                    func_002734E8(s, 0);
                else
                    s->owner->SetCarry(0);
            }
            break;
        }
        if (s->state == previous || s->state == -1)
            break;
    }
    if (s->owner->movement != 1)
        return;
    ASEGA *animation = s->owner->animation;
    TRACKREF *reference = animation ? func_00136EE0(animation->definition, s->owner, 6, 1) : 0;
    if (reference) {
        TRACK *track = reference->track;
        VE *vt = track->vt;
        ((EVAL)vt[3].pfn)((char *)track + vt[3].delta, 0, &w.scratch, animation->time, animation->scale);
        V *direction = &s->owner->direction;
        float height = w.scratch.f[2];
        direction->f[0] = 0.0f;
        direction->f[2] = height;
        direction->f[1] = 0.0f;
    } else
        s->owner->direction.q = D_00317560.q;
}
