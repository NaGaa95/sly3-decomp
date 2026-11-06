// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Re-anchor the camera of a vehicle-like owner on its recorded trail. With flag 0 and few wheels in contact the camera is
// placed straight behind the owner; otherwise every recorded trail entry whose wheel outline fits (clear segment between the
// two wheel pairs, ground below each wheel) is collected, the list is sorted by distance and the nearest entry is used.
// Matching notes: the camera block's TrailEntry is a BLK local whose slot the loop's Mat4 reuses; the request is built in a
// block-local helper so its slot is freed too; Build keeps the rotation source address (`src`) live across the position call
// (its own register), BuildDirect copies straight from the frame; the candidate store is `list[n++]`; the distance word goes
// through SetX so the store is not moved into the destructor's delay slot.
typedef int qword __attribute__((mode(TI)));
struct VTE { short delta, pad; void *fn; };
struct Mat3 { qword rows[3]; };
struct Mat4 { Mat3 rot; qword position; };
union Vec { qword q; float f[4]; int bits[4]; };
struct TrailEntry { qword position; Mat3 rot; };
struct Wheel { char pad00[0x14]; float radius; char pad18[8]; Vec point; char pad30[0x30]; };
struct Hit { qword a, b, c, d; float t; int pad[3]; qword e; };
struct Candidate { TrailEntry *entry; float distance; };
struct Owner {
    char pad00[0xC]; VTE *vt; char pad10[0xDC - 0x10]; int world; char padE0[0x190 - 0xE0];
    Wheel wheels[4]; char pad310[0x45C - 0x310]; int count; TrailEntry entries[32];
    char padC60[0xC70 - 0xC60]; Mat4 anchor;
};
struct AL { int cb; int cbAlign; AL(int c, int a) { cb = c; cbAlign = a; } };
struct FRAME { FRAME(); ~FRAME(); };
extern char D_00475480[];
extern "C" {
int func_00205888(Owner *);
int func_00205A38(Owner *);
void func_0011CCF8(void *, void *, Mat3 *);
qword *func_002BA818(qword *, qword);
void func_00204CB0(Owner *, float, float, float, float, float);
void func_0025CDD0();
void func_0025D0D8(void *, qword, void (*)(), int, float, int *, void ***);
qword func_001C9828(Mat4 *, const Mat4 *, qword);
void *func_00165000(int, qword, qword, int, void **, Hit *);
void *func_001D25B0(AL *);
void func_00292540(void *, int, int, int (*)(const void *, const void *));
int func_002047A8(const void *, const void *);
}
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Length(qword v)
{
    qword d, one, len;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(len) : "j"(d));
    return len;
}
// The low word of a VU qword stored straight from the GPR gcc moves it to (as src/game_middle/func_001B4430.cpp's SetX); the
// second, unused "j" input only keeps the qword's pseudo in a VU register.
static inline void SetX(float *pg, qword q) { __asm__("sw %1,%0" : "=m"(*pg) : "r"(q), "j"(q)); }
static inline Mat4 *PlacementOf(Owner *o)
{
    VTE *entry = &o->vt[36];
    return ((Mat4 *(*)(void *))entry->fn)((char *)o + entry->delta);
}
// Matrix of a trail entry: position (copied with the vector setter), rotation, and the homogeneous w lanes.
static inline void Build(Mat4 *m, const TrailEntry *e)
{
    const Mat3 *src = &e->rot;
    func_002BA818(&m->position, e->position);
    m->rot = *src;
    Vec *w = (Vec *)m;
    w[2].bits[3] = 0;
    w[1].bits[3] = 0;
    w[0].bits[3] = 0;
    w[3].f[3] = 1.0f;
}
static inline void BuildDirect(Mat4 *m, const TrailEntry *e)
{
    func_002BA818(&m->position, e->position);
    m->rot = e->rot;
    Vec *w = (Vec *)m;
    w[2].bits[3] = 0;
    w[1].bits[3] = 0;
    w[0].bits[3] = 0;
    w[3].f[3] = 1.0f;
}
static inline Candidate *AllocList(int n)
{
    AL req(n * 8, 0x10);
    return (Candidate *)func_001D25B0(&req);
}
extern "C" int func_002047D0(Owner *p, int flag)
{
    int result = 0;
    if (!flag && !func_00205888(p) && func_00205A38(p) < 3) {
        result = 1;
        TrailEntry fixed;
        Vec *pos = (Vec *)&fixed.position;
        pos->q = PlacementOf(p)->position;
        pos->f[2] += 60.0f;
        func_0011CCF8(PlacementOf(p), 0, &fixed.rot);
        BuildDirect(&p->anchor, &fixed);
        func_00204CB0(p, 200.0f, -200.0f, 1.0f, -1.0f, 2.0f);
    } else if (p->count) {
        FRAME outer;
        int n = 0;
        Candidate *list = AllocList(p->count);
        for (int i = 0; i < p->count; i++) {
            TrailEntry *e = &p->entries[i];
            FRAME inner;
            int count;
            void **objects;
            func_0025D0D8(D_00475480, e->position, func_0025CDD0, p->world, 300.0f, &count, &objects);
            Mat4 m;
            Vec a, b, down;
            Hit hit;
            Build(&m, e);
            a.q = func_001C9828(&m, 0, p->wheels[0].point.q);
            b.q = func_001C9828(&m, 0, p->wheels[3].point.q);
            if (func_00165000(0, a.q, b.q, count, objects, &hit))
                continue;
            down = a;
            down.f[2] -= 2.0f * p->wheels[0].radius;
            if (!func_00165000(0, a.q, down.q, count, objects, &hit))
                continue;
            down = b;
            down.f[2] -= 2.0f * p->wheels[3].radius;
            if (!func_00165000(0, b.q, down.q, count, objects, &hit))
                continue;
            a.q = func_001C9828(&m, 0, p->wheels[1].point.q);
            b.q = func_001C9828(&m, 0, p->wheels[2].point.q);
            if (func_00165000(0, a.q, b.q, count, objects, &hit))
                continue;
            down = a;
            down.f[2] -= 2.0f * p->wheels[1].radius;
            if (!func_00165000(0, a.q, down.q, count, objects, &hit))
                continue;
            down = b;
            down.f[2] -= 2.0f * p->wheels[2].radius;
            if (!func_00165000(0, b.q, down.q, count, objects, &hit))
                continue;
            Candidate *c = &list[n++];
            c->entry = e;
            SetX(&c->distance, Length(Sub(PlacementOf(p)->position, e->position)));
        }
        if (n) {
            func_00292540(list, n, 8, func_002047A8);
            result = 1;
            Mat4 *anchor = &p->anchor;
            Build(anchor, list[0].entry);
            func_00204CB0(p, 500.0f, -500.0f, 1.0f, -1.0f, flag ? ((Vec *)anchor)[2].f[3] : 2.0f);
        }
    }
    return result;
}
