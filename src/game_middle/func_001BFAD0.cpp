// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// State setter of a path-riding object (p->path is the path mesh, p->u the path parameter). Leaving state -1 attaches the actor:
// path mode 5, samples the path 50 units ahead and behind to decide whether it descends (normalized z < -0.5, fallback vector
// D_00317550), clamps u to the limits from func_001BF128, places the actor's offset and every node offset relative to the path point
// and starts the attach effect; leaving state 0 restarts the idle animation. Entering -1 detaches (path mode 6, node offsets
// relative to the actor matrix, detach effect, stops the channel or notifies the two actor objects at 0x1AA0 / 0x1AA8) and clears the path; the other
// states pick the animation, start time, speed and blend flags before the animation starts.
// Source-shape notes: the path samples, the limits and the result of func_001C9428 are memory locals declared at first use
// (that gives the original stack slots 0x00..0x40); the node offset is a vector union whose z is cleared.
typedef unsigned long long qword __attribute__((mode(TI)));
struct VE { short delta, pad; void *fn; };
struct VECTOR { float x, y, z, w; } __attribute__((aligned(16)));
struct LM { float gMin, gMax; };
struct MAT { float m[3][4]; qword pos; };
struct OBJ { char pad0[0xC]; VE *vt; };
union VU { qword q; float f[4]; };
struct NODE { qword pos; VU offset; char pad20[0x64 - 0x20]; NODE *next; };
struct ACTOR
{
    char pad0[0xC]; VE *vt;
    char pad10[0x158 - 0x10]; NODE *nodes;
    char pad15C[0x1A0 - 0x15C]; VECTOR v1A0;
    char pad1B0[0x1120 - 0x1B0]; qword offset;
    char pad1130[0x113C - 0x1130]; int anim113C; int anim1140;
    char pad1144[0x1AA0 - 0x1144]; OBJ *x1AA0; int pad1AA4; OBJ *x1AA8;
};
struct PATH
{
    char pad0[0xC]; VE *vt;
    char pad10[0x180 - 0x10]; int x180;
    char pad184[0x1E0 - 0x184]; int effectOn; int effectOff;
};
struct ANIM { char pad0[0x64]; float duration; };
struct S
{
    ACTOR *actor; int state; float tState; PATH *path; float u; int pad14; int descending; int x1C; int oldState;
    char pad24[0x30 - 0x24]; qword x30;
    char pad40[0x70 - 0x40]; ANIM *anim70; ANIM *anim74; ANIM *anim78; ANIM *anim7C; ANIM *anim80; int channel;
};
struct CLOCK { float t; float dt; };
extern CLOCK g_clock;
extern qword D_00317550;
extern "C" {
void func_0013BD00(PATH *, ACTOR *);
void func_0013BD88(PATH *, ACTOR *);
void func_0024F3B8(ACTOR *, PATH *, int);
float func_0022E0B8(PATH *, float);
void func_0022E330(PATH *, float, qword *, qword *);
void func_001BF128(S *, LM *);
float func_0011EE68(LM *, float);
qword func_001C9428(ACTOR *, int, qword);
void func_001F47C8(ACTOR *, int);
void *func_002459F8(int);
void func_00244F08(void *, ACTOR *);
void func_00245000(void *, qword);
void func_00137588(ANIM *, ACTOR *, float, float, int, int *);
void func_00137628(int *);
void func_0023AC58(int *);
void func_001C8FB0(OBJ *, OBJ *);
}
static inline void Mode(PATH *a, int n) { VE *v = &a->vt[3]; ((void (*)(void *, int, int, int, int, int))v->fn)((char *)a + v->delta, n, 0, 0, 0, 0); }
static inline void CallObj(OBJ *a, int slot) { VE *v = &a->vt[slot]; ((void (*)(void *))v->fn)((char *)a + v->delta); }
static inline MAT *Matrix(ACTOR *a) { VE *v = &a->vt[36]; return (MAT *)((char *(*)(void *))v->fn)((char *)a + v->delta); }
static inline void Clear(VECTOR &v) { float *f = &v.x; f[1] = f[2] = 0.0f; v.x = 0.0f; }
static inline qword QwSub(qword a, qword b) { qword d; __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
static inline qword QwLength(qword v)
{
    qword qw, qw2, vfOne;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(qw), "=j"(vfOne) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(qw2) : "j"(qw));
    return qw2;
}
static inline float F(qword q) { float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(q)); return g; }
static inline qword DivQ(qword qw, qword v)
{
    qword r;
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(qw), "j"(v));
    return r;
}
static inline qword QwNormalize(qword v)
{
    qword qw = QwLength(v);
    qword fb = D_00317550;
    if (F(qw) < 1.0e-4f)
        return fb;
    return DivQ(qw, v);
}
static inline float Z(qword q) { float w; __asm__("pextuw %0, $zero, %1" : "=&r"(w) : "r"(q)); return w; }

extern "C" void func_001BFAD0(S *p, int state)
{
    int old = p->state;
    if (state == old)
        return;
    switch (old)
    {
    case -1:
    {
        Mode(p->path, 5);
        func_0013BD00(p->path, p->actor);
        func_0024F3B8(p->actor, p->path, 1);
        p->oldState = old;
        VU ahead, behind;
        func_0022E330(p->path, func_0022E0B8(p->path, p->u + 50.0f), &ahead.q, 0);
        func_0022E330(p->path, func_0022E0B8(p->path, p->u - 50.0f), &behind.q, 0);
        p->descending = Z(QwNormalize(QwSub(ahead.q, behind.q))) < -0.5f;
        LM lm;
        func_001BF128(p, &lm);
        p->u = func_0011EE68(&lm, p->u);
        VU pos;
        func_0022E330(p->path, p->u, &pos.q, 0);
        VU r;
        r.q = func_001C9428(p->actor, 0, p->x30);
        p->actor->offset = QwSub(pos.q, r.q);
        for (NODE *n = p->actor->nodes; n; n = n->next)
        {
            n->offset.q = QwSub(n->pos, pos.q);
            n->offset.f[2] = 0.0f;
        }
        func_001F47C8(p->actor, p->path->x180);
        if (p->path->effectOn)
        {
            void *e = func_002459F8(p->path->effectOn);
            func_00244F08(e, 0);
            func_00245000(e, pos.q);
        }
        break;
    }
    case 0:
        func_00137588(p->anim80, p->actor, 0.0f, 1.0f, 1, &p->channel);
        break;
    }
    p->state = state;
    ANIM *anim = 0;
    int flags = 1;
    float start = 0.0f;
    float speed = 1.0f;
    p->tState = g_clock.t;
    switch (state)
    {
    case -1:
        Mode(p->path, 6);
        func_0013BD88(p->path, p->actor);
        func_0024F3B8(p->actor, p->path, 0);
        for (NODE *n = p->actor->nodes; n; n = n->next)
        {
            qword pos = n->pos;
            n->offset.q = QwSub(pos, Matrix(p->actor)->pos);
            n->offset.f[2] = 0.0f;
        }
        func_001F47C8(p->actor, 0);
        if (p->path->effectOff)
        {
            void *e = func_002459F8(p->path->effectOff);
            func_00244F08(e, 0);
            func_00245000(e, Matrix(p->actor)->pos);
        }
        if (p->channel)
            func_00137628(&p->channel);
        else if (p->anim80)
        {
            ACTOR *a = p->actor;
            CallObj(a->x1AA0, 8);
            func_001C8FB0(a->x1AA0, a->x1AA8);
            CallObj(a->x1AA8, 9);
        }
        p->path = 0;
        return;
    case 0:
        anim = p->anim74;
        if (!anim)
        {
            anim = p->anim7C;
            start = anim->duration * 0.5f;
            speed = 0.5f;
        }
        p->x1C = 0;
        break;
    case 1:
        anim = p->anim78;
        flags = 9;
        break;
    case 2:
        anim = p->anim70;
        flags = 9;
        break;
    case 3:
        anim = p->anim70;
        speed = -1.0f;
        flags = 9;
        break;
    case 4:
        p->descending = !p->descending;
        anim = p->anim7C;
        break;
    }
    func_0023AC58(&p->actor->anim1140);
    func_00137588(anim, p->actor, start, speed, flags, &p->actor->anim113C);
    Clear(p->actor->v1A0);
}
