// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Reference: Sly 2 src/hand/func_00202D38.cpp; target Sly 3 0x0024CCB0.
// Per-frame update of the interaction prompt controller (func_0024C6D8 changes its state): screen projection of the
// actor's head through the camera (proximity / size gain), the state machine, then the input check.
typedef int qword __attribute__((mode(TI)));
struct VT { short adjustment, unused; void *function; };
struct XF { char pad0[0x10]; qword up; char pad20[0x10]; qword pos; };
struct LINK { char pad0[0x44]; int state; };
struct ACTOR { char pad0[0xC]; VT *vtable; char pad10[0xC4]; float headOffset, threshold; LINK *link; char padE0[0x18]; int state, mode, choice; };
struct CAMERA { char pad0[0xC]; VT *vtable; };
struct DISPLAY { char pad0[0x120]; int actorChoice, risingChoice, fallingChoice, nearChoice, emptyChoice; };
struct MODEL { CAMERA *x; char pad4[0x14]; int state; };
struct P { int state; char pad4[0xC]; qword origin; char pad20[0x10]; int count; ACTOR *items[22]; ACTOR *actor; float proximity, sizeGain; int rising; float choiceTime; int savedFlags; void *resource; MODEL *model; DISPLAY *primary, *secondary; int refreshPending, visible, selected, pending; };
struct CLOCK { float time, dt; };
struct PLAYER { char pad0[0x134]; void *control; };
struct VU_FLOAT { qword qw; };
extern CLOCK g_clock;
extern PLAYER *D_00370AC0;
extern "C" {
void func_001BDB50(MODEL *);
void func_00262280(DISPLAY *, int);
void func_0024C478(P *);
void func_0024BFB0(P *);
int func_0024C1E8(P *);
void func_0024C6D8(P *, int);
CAMERA *func_001F4A80(CAMERA *);
qword func_001678C8(CAMERA *, qword);
void func_00261580(DISPLAY *, int, float);
int func_00260758(DISPLAY *, int);
void func_00262450(DISPLAY *, int);
int func_0024D6B0(ACTOR *);
int func_001A7A80(void *, int, float);
}
static inline XF *Xf(ACTOR *a) { VT *entry = &a->vtable[36]; return ((XF *(*)(void *))entry->function)((char *)a + entry->adjustment); }
static inline XF *Xf(CAMERA *a) { VT *entry = &a->vtable[36]; return ((XF *(*)(void *))entry->function)((char *)a + entry->adjustment); }
static inline VU_FLOAT VuFloatFromMemWord(const float &f) { VU_FLOAT v; __asm__("qmtc2.ni %1,%0" : "=j,!r"(v.qw) : "r,m"(f)); return v; }
static inline qword QwScaleX(qword a, qword s) { qword r; __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(r) : "j"(a), "j"(s)); return r; }
static inline qword QwAdd(qword a, qword b) { qword r; __asm__("vadd.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword QwSub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword QwLengthXY(qword v) { qword r; __asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y" : "=j"(r) : "j"(v)); __asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(r) : "0"(r)); return r; }
static inline float GXOfQw(qword qw) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(qw)); return x; }
static inline float GYOfQw(qword qw) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(qw)); return y; }
static inline float GZOfQw(qword qw) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(qw)); return z; }
// screen position of a projected point: x and y from [-1,1] to pixels, z kept
static inline VU_FLOAT ScreenFromProjected(qword q)
{
    VU_FLOAT v;
    int t;
    float x = GXOfQw(q) * 320.0f + 320.0f;
    float y = GYOfQw(q) * -240.0f + 240.0f;
    float z = GZOfQw(q);
    __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0" : "=&r"(v.qw), "=&r"(t) : "f"(x), "f"(y), "f"(z));
    return v;
}
static inline float Min(float a, float b) { return a < b ? a : b; }
static inline float Max(float a, float b) { return a < b ? b : a; }
static inline float GClamp(float g, float gMin, float gMax) { return Max(gMin, Min(g, gMax)); }
extern "C" void func_0024CCB0(P *p)
{
    if (!p->primary)
        return;
    if (!p->secondary)
        return;
    if (p->refreshPending) {
        p->refreshPending = 0;
        func_001BDB50(p->model);
    }
    if (p->choiceTime + 5.0f < g_clock.time)
        func_00262280(p->primary, 0x3DA);
    if (p->state < 8)
        if (p->state >= 2) {
            func_0024C478(p);
            func_0024BFB0(p);
            if (!func_0024C1E8(p))
                func_0024C6D8(p, 1);
        }
    if (p->actor) {
        CAMERA *camera = func_001F4A80(p->model->x);
        qword world = Xf(p->actor)->pos;
        XF *xf = Xf(camera);
        VU_FLOAT offset = VuFloatFromMemWord(p->actor->headOffset);
        qword head = QwAdd(world, QwScaleX(xf->up, offset.qw));
        qword base = func_001678C8(camera, world);
        qword top = func_001678C8(camera, head);
        VU_FLOAT screen = ScreenFromProjected(base);
        float distance = GXOfQw(QwLengthXY(QwSub(screen.qw, p->origin)));
        VU_FLOAT screenTop = ScreenFromProjected(top);
        float size = GXOfQw(QwLengthXY(QwSub(screen.qw, screenTop.qw)));
        float proximity = 1.0f - (distance - 128.0f) / 128.0f;
        size = size / 120.0f;
        p->rising = 1;
        p->proximity = GClamp(proximity, 0.0f, 1.0f);
        p->sizeGain = size;
        if (size > 1.0f) {
            p->rising = 0;
            p->sizeGain = 2.0f - size;
        }
        p->sizeGain = Max(p->sizeGain, 0.0f);
    }
    switch (p->state) {
    case -1:
        break;
    case 2:
        if (p->actor && p->actor->state != 2)
            func_0024C6D8(p, 4);
        break;
    case 4:
        if (!p->actor)
            func_0024C6D8(p, 2);
        else if (p->actor->state == 3)
            func_0024C6D8(p, 3);
        else if (p->proximity >= 1.0f) {
            if (p->rising)
                func_0024C6D8(p, 5);
            else
                func_0024C6D8(p, 6);
        }
        break;
    case 3:
        if (!p->actor)
            func_0024C6D8(p, 2);
        else if (p->actor->state != 3)
            func_0024C6D8(p, 4);
        break;
    case 5:
        if (!p->actor)
            func_0024C6D8(p, 2);
        else if (p->proximity < 1.0f)
            func_0024C6D8(p, 4);
        else if (p->sizeGain >= 1.0f - p->actor->threshold)
            func_0024C6D8(p, 7);
        else
            func_00261580(p->secondary, 0x3D9, p->sizeGain);
        break;
    case 6:
        if (!p->actor)
            func_0024C6D8(p, 2);
        else if (p->proximity < 1.0f)
            func_0024C6D8(p, 4);
        else if (p->sizeGain >= 1.0f - p->actor->threshold)
            func_0024C6D8(p, 7);
        else
            func_00261580(p->secondary, 0x3D9, p->sizeGain);
        break;
    case 7:
        if (p->actor) {
            if (p->proximity < 1.0f || p->sizeGain < 1.0f - p->actor->threshold) {
                if (p->rising)
                    func_0024C6D8(p, 5);
                else
                    func_0024C6D8(p, 6);
            }
        } else
            func_0024C6D8(p, 2);
        break;
    case 8:
        if (!func_00260758(p->primary, 0x3D7)) {
            int changed = 0;
            if (p->actor && p->actor->state == 1 && p->proximity >= 1.0f && p->sizeGain >= 1.0f - p->actor->threshold) {
                if (!p->actor->mode)
                    func_0024C6D8(p, 9);
                else {
                    p->pending = p->actor->choice;
                    func_0024C6D8(p, 7);
                    changed = 1;
                }
            } else {
                if (p->actor && p->actor->state != 1) {
                    p->pending = p->primary->actorChoice;
                    func_0024C6D8(p, 3);
                } else if (p->proximity >= 1.0f && p->rising) {
                    p->pending = p->primary->risingChoice;
                    func_0024C6D8(p, 5);
                } else if (p->proximity >= 1.0f && !p->rising) {
                    p->pending = p->primary->fallingChoice;
                    func_0024C6D8(p, 6);
                } else if (p->actor) {
                    p->pending = p->primary->nearChoice;
                    func_0024C6D8(p, 4);
                } else {
                    p->pending = p->primary->emptyChoice;
                    func_0024C6D8(p, 2);
                }
                changed = 1;
            }
            if (changed) {
                func_00262450(p->primary, 0x3DA);
                p->choiceTime = g_clock.time;
            }
        }
        break;
    case 9:
        if (!func_00260758(p->primary, 0x3DB)) {
            int ready = 1;
            func_0024C6D8(p, 2);
            for (int i = 0; i < p->count; i++) {
                ACTOR *actor = p->items[i];
                int done = func_0024D6B0(actor);
                // an actor whose link is missing or in state 1 must be done before the refresh
                int linkReady = !actor->link || actor->link->state == 1;
                if (!done && linkReady) {
                    ready = 0;
                    break;
                }
            }
            if (ready)
                p->refreshPending = 1;
        }
        break;
    case 10:
        if (!func_00260758(p->primary, 0x37B))
            func_0024C6D8(p, -1);
        break;
    case 0:
        if (func_00260758(p->primary, 0x37B))
            func_0024C6D8(p, 1);
        break;
    case 1:
        func_0024BFB0(p);
        if (func_0024C1E8(p))
            func_0024C6D8(p, 2);
        break;
    }
    if (p->model->state != 1) {
        switch (p->state) {
        case 2: case 3: case 4: case 5: case 6:
            if (func_001A7A80(D_00370AC0->control, 10, 0.0f))
                func_0024C6D8(p, 8);
            break;
        case 7:
            if (func_001A7A80(D_00370AC0->control, 250, 0.0f))
                func_0024C6D8(p, 8);
            break;
        }
    }
}
