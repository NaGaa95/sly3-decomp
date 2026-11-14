// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// vsqrt with untied input (its input pseudo dies -> sched1 issues it before the lw of name->identity) and the
// XY length read through an mtc1 asm with an "r" input (gcc emits the qmfc2, raising the sqrt chain priority in sched2).
// Adapted from the Sly 2 decomp (func_001758A0): pick the first enabled response ENTRY of p that accepts target
// (range, height, angle, optional line of sight), ask p's HandleSpliceEvent(0x1B) about it, then run the response.
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
struct M4 { U row[4]; };
struct VTE { short delta, pad; void *fn; };
struct NAME { unsigned identity; };
struct LM { float low, high; };
struct ENTRY {
    char pad0[0x40];
    LM distance, height;
    char pad50[8];
    float angle, minHit;
    int lineOfSight, pad64, response;
    char pad6C[0x2C];
    int enabled;
};
struct P {
    char pad0[0xC];
    VTE *vt;
    char pad10[0x18];
    unsigned long : 56;
    unsigned long flags : 8;
    char pad30[0x8];
    NAME *name;
    char pad3C[0x1058 - 0x3C];
    ENTRY *entries[8];
    int count;
    ENTRY *current;
    float cooldown;
};
struct FRAME { int n; FRAME(); ~FRAME(); };
struct LSG { U point; char rest[0x50]; };
struct LOS { U start, end; LSG hit; };
extern "C" void func_0012BC20(void *);
struct CREF {
    short tagk;
    int tag;
    CREF(bool f) { tagk = 0x15; tag = f; }
    ~CREF() { func_0012BC20(this); }
};
struct POLY { float a, b, c; };
struct CLOCK { float time; };
struct BASIC {
    char pad0[0xC];
    virtual void VUnk00();
    virtual void VUnk01();
    virtual void HandleSpliceEvent(unsigned symidEvent, int fPost, int cargs, void **ppvargs, CREF *pref);
};
/* .rodata of the original unit at 0x003221E0. */
static const POLY D_003221E0 = { 0.0f, 0.005f, 0.0f };
extern "C" {
extern CLOCK g_clock;
extern LM D_00341FF0;
extern char D_00475480[];
int func_0013B500(P *, int);
int func_00256500(void *, P *);
unsigned func_001FA5B8(unsigned);
float func_002575C0(P *);
int func_0011EE30(LM *, float);
qword func_001C9428(P *, P *, qword);
float func_001205C8(qword);
int func_001A3B28(void *, void *);
void func_0025CF18(void *, qword, qword, int (*)(void *, void *), void *, int *, void ***);
int func_00165000(int, qword, qword, int, void **, LSG *);
void func_00256828(P *, ENTRY *, void *, qword);
void func_002566F0(void *, int);
ENTRY *func_001A3BA8(P *p, P *target, void *gate);
}
static inline qword QwSub(qword qw0, qword qw1)
{
    qword qw;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(qw) : "j"(qw0), "j"(qw1));
    return qw;
}
static inline qword QwLengthXY(qword v)
{
    qword qw;
    qword r;
    __asm__("vmul.xy %0, %1, %2\n\tvaddy.x %0, %0, %0y" : "=j"(qw) : "j"(v), "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(r) : "j"(qw));
    return r;
}
static inline qword QwLength(qword v)
{
    qword qw;
    qword vfOne;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(qw), "=j"(vfOne) : "j"(v));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(qw) : "0"(qw));
    return qw;
}
static inline float GFromVf(qword qw)
{
    float g;
    __asm__("qmfc2 %0, %1" : "=r"(g) : "j"(qw));
    return g;
}
static inline float GXOfQw(qword qw)
{
    float g;
    __asm__("mtc1 %1, %0" : "=f"(g) : "r"(qw));
    return g;
}
static inline float GLengthXY(qword v)
{
    return GXOfQw(QwLengthXY(v));
}
static inline float GLength(qword v)
{
    return GFromVf(QwLength(v));
}
static inline float GZOfQw(qword qw)
{
    float z;
    __asm__("pextuw %0, $0, %1" : "=r"(z) : "r"(qw));
    return z;
}
static inline qword PosOf(P *p)
{
    VTE *e = &p->vt[36];
    return ((M4 *(*)(void *))e->fn)((char *)p + e->delta)->row[3].q;
}
static inline int Blocked(LOS *line, float limit)
{
    return GLength(QwSub(line->start.q, line->hit.point.q)) < limit;
}

ENTRY *func_001A3BA8(P *p, P *target, void *gate)
{
    qword from, to;
    float height, distance;
    int i;

    if (p->current)
        return 0;
    if (!target)
        return 0;
    {
        int enabled = (int)target->flags & 1;
        if (!enabled)
            return 0;
    }
    if (g_clock.time < p->cooldown)
        return 0;
    if (func_0013B500(target, 0x31)) {
        VTE *e = &target->vt[81];
        if (((int (*)(void *))e->fn)((char *)target + e->delta))
            return 0;
    }
    if (gate && !func_00256500(gate, p))
        return 0;
    from = PosOf(p);
    to = PosOf(target);
    {
        qword d = QwSub(to, from);
        distance = GLengthXY(d);
        height = GZOfQw(d);
    }
    if (func_001FA5B8(target->name->identity) == func_001FA5B8(p->name->identity))
        distance += ((unsigned)target < (unsigned)p) ? 75.0f : -75.0f;
    {
        float s = func_002575C0(p);
        distance /= s;
        height /= s;
    }
    for (i = 0; i < p->count; i++) {
        ENTRY *entry = p->entries[i];
        float angle, gain;
        if (!entry->enabled)
            continue;
        if (!func_0011EE30(&entry->distance, distance))
            continue;
        if (!func_0011EE30(&entry->height, height))
            continue;
        angle = __builtin_fabsf(func_001205C8(func_001C9428(0, p, to)));
        gain = D_003221E0.a + distance * (D_003221E0.b + distance * D_003221E0.c);
        {
            float lo = D_00341FF0.low, hi = D_00341FF0.high;
            if (gain < lo)
                gain = lo;
            else if (hi < gain)
                gain = hi;
        }
        if (entry->angle < gain * angle)
            continue;
        if (entry->lineOfSight) {
            FRAME frame;
            LOS line;
            int count;
            void **objects;
            line.start.q = from;
            line.end.q = to;
            func_0025CF18(D_00475480, from, to, func_001A3B28, entry, &count, &objects);
            if (func_00165000(0, line.start.q, line.end.q, count, objects, &line.hit) &&
                Blocked(&line, entry->minHit))
                continue;
        }
        {
            CREF ref(true);
            void *argument = (char *)entry + 0x18;
            ((BASIC *)p)->HandleSpliceEvent(0x1B, 0, 1, &argument, &ref);
            if (ref.tagk != 0x15 || !ref.tag)
                continue;
            if (entry->response) {
                M4 frame;
                VTE *e = &target->vt[37];
                void *owner = ((void *(*)(void *, M4 *))e->fn)((char *)target + e->delta, &frame);
                func_00256828(p, entry, owner, frame.row[3].q);
                entry = 0;
                if (gate)
                    func_002566F0(gate, 3);
            }
            return entry;
        }
    }
    return 0;
}
