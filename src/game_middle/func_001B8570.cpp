// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Slides a movement vector (*out) along the actor's contact planes. The contact normals (flipped when the contact
// belongs to another actor, skipped when nearly vertical) are projected off the up axis and collected (at most 64);
// a Gram matrix of the normals is handed to func_0011BA98 together with the right-hand side normal . *out, and the
// returned weights are subtracted from *out. When the removed part is long (squared length above 1) the
// caller-visible mode is advanced through func_001B77F8 (0 -> 1, 2 -> 3).
typedef int qword __attribute__((mode(TI)));
typedef unsigned int uint;
union U { qword q; float f[4]; int i[4]; };
struct ACTOR;
struct CONTACT { char pad0[8]; ACTOR *owner; char padC[0x80 - 0xC]; U normal; char pad90[0x1C]; CONTACT *next; };
struct GROUP { CONTACT *first; GROUP *next; };
struct COLLISION { char pad0[0x64]; GROUP *groups; CONTACT *single; };
struct ACTOR { char pad0[0xDC]; COLLISION *collision; };
struct MOVE { ACTOR *actor; char pad4[0x18]; int mode; };
struct REQ { int bytes, alignment; };
union SCRATCH { U scalar; REQ request; };
class FRAME { public: FRAME(); ~FRAME(); };
extern "C" {
extern U D_00317550;
extern float D_0032302C;
int func_001BADC0(ACTOR *actor);
void *func_001D25B0(REQ *r);
void func_0011BA98(int count, float limit, float *matrix, float *rhs, float *weights);
void func_001B77F8(MOVE *p, int mode, int flag);
}
static inline qword Scalar(float f)
{
    qword q;
    __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f));
    return q;
}
static inline qword ScalarWord(const float &f)
{
    qword q;
    register int bits __asm__("$7") = *(const int *)&f; // the one pin: the weight word is loaded into $a3 (reload would take $a1)
    __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(bits));
    return q;
}
static inline float GetZ(qword q)
{
    float f;
    __asm__("pextuw %0, $0, %1" : "=r"(f) : "r"(q));
    return f;
}
static inline float GetXM(qword q)
{
    float f;
    __asm__("mtc1 %1, %0" : "=f"(f) : "r"(q));
    return f;
}
static inline qword Reject(qword value, qword up)
{
    qword q, one;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(q), "=&j"(one) : "j"(value), "j"(up));
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(q) : "j"(up), "j"(q));
    __asm__("vsub.xyzw %0, %0, %1" : "+j"(value) : "j"(q));
    return value;
}
static inline void StoreDot(float *out, const qword &a0, const qword &b)
{
    qword a = a0;
    qword one;
    __asm__("vmul.xyz %1, %1, %3\n\tvaddw.x %2, $vf0, $vf0w\n\tvadday.x $ACC, %1, %1y\n\tvmaddz.x %1, %2, %1z\n\tqmfc2.ni %0, %1" : "=&rV"(*out), "+j"(a), "=j"(one) : "j"(b), "j"(a));
}
static inline void StoreDotRhs(float *out, qword input, const qword &source0)
{
    qword q = source0;
    qword one;
    __asm__("vmul.xyz %1, %3, %1\n\tvaddw.x %2, $vf0, $vf0w\n\tvadday.x $ACC, %1, %1y\n\tvmaddz.x %1, %2, %1z\n\tqmfc2.ni %0, %1" : "=&rV"(*out), "+j"(q), "=j"(one) : "j"(input));
}
static inline qword AddScaled(qword sum, qword v, qword k)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(sum), "j"(v), "j"(k));
    return r;
}
static inline float *Allocate(REQ *r, int bytes)
{
    r->bytes = bytes;
    r->alignment = 16;
    return (float *)func_001D25B0(r);
}
extern "C" void func_001B8570(MOVE *p, U *out)
{
    struct { U normals[64]; SCRATCH scratch; } w;
    CONTACT *c;
    GROUP *group;
    if (func_001BADC0(p->actor)) {
        out->f[2] = 0.0f;
        out->f[1] = 0.0f;
        out->f[0] = 0.0f;
        return;
    }
    int count = 0;
    group = p->actor->collision->groups;
    for (;;) {
        c = group ? group->first : p->actor->collision->single;
        if (c) {
            unsigned base = (unsigned)w.normals - 16;
            unsigned write = base + count * 16;
            do {
                if ((uint)count >= 64)
                    goto collected;
                qword normal = c->normal.q;
                if (p->actor != c->owner) {
                    w.scratch.scalar.q = Scalar(-1.0f);
                    __asm__("vmulx.xyzw %0, %0, %1x" : "+j"(normal) : "j"(w.scratch.scalar.q));
                }
                if (GetZ(normal) > 0.9f)
                    continue;
                write += 16;
                *(qword *)write = Reject(normal, D_00317550.q);
                count++;
            } while ((c = c->next) != 0);
        }
        if (!group)
            break;
        group = group->next;
    }
collected:
    if (!count)
        return;
    FRAME frame;
    qword residual, original;
    float *matrix = Allocate(&w.scratch.request, count * count * 4);
    float *rhs = Allocate(&w.scratch.request, count * 4);
    float *weights = Allocate(&w.scratch.request, count * 4);
    float *cursor = matrix;
    int i, j;
    for (i = 0; i < count; i++)
        for (j = 0; j < count; j++)
            { StoreDot(cursor, w.normals[i].q, w.normals[j].q); cursor++; }
    residual = out->q;
    original = out->q;
    cursor = rhs;
    for (i = 0; i < count; i++)
        { StoreDotRhs(cursor, residual, w.normals[i].q); cursor++; }
    func_0011BA98(count, D_0032302C, matrix, rhs, weights);
    if (count > 0) {
        float *wp = weights;
        i = count;
        cursor = (float *)w.normals;
        do {
            w.scratch.scalar.q = ScalarWord(*wp);
            residual = AddScaled(residual, *(qword *)cursor, w.scratch.scalar.q);
            wp++;
            cursor += 4;
        } while (--i);
    }
    qword d = original;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(original), "j"(residual));
    qword sq, one;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(sq), "=j"(one) : "j"(d));
    if (GetXM(sq) > 1.0f) {
        switch (p->mode) {
        case 0: func_001B77F8(p, 1, 0); break;
        case 2: func_001B77F8(p, 3, 0); break;
        }
    }
    out->q = residual;
}
