// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Grow the shared bounds record of a body: when the body has the two bound flags (bits 32/33) and no record yet, walk up the
// parent chain to the first body that has one (or the first root / body whose state field is 1, which creates a new record from the
// pool), attach it and count the user. Then widen the record's low/high radius by this body's radius plus its distance to the
// record origin. Based on Sly 2 func_001F2500.
typedef int qword __attribute__((mode(TI)));
typedef unsigned long ulong;
struct Node;
struct Origin { char pad[0x70]; qword pos; };
struct M4 { qword a, b, c, d; };
struct Stats { struct Node *owner; qword *origin; int count, unusedC; float low; int unused14, unused18; float high, scale; };
struct VTE { short d; short p; void *fn; };
struct Node {
    char pad0[0xC]; VTE *vt; Node *parent;
    char pad14[0x50 - 0x14]; Origin *reference;
    char pad54[0x90 - 0x54]; float radius;
    char pad94[0xC0 - 0x94]; ulong flags;
    char padC8[0x10C - 0xC8]; Stats *stats;
    int unused110; float scale;
    char pad118[8]; ulong state;
};
extern char D_00479A48[];
extern "C" Stats *func_0011E118(void *);
extern "C" void func_0023B3A8(Node *);
static inline float Distance(qword a, qword b)
{
    qword d, one;
    float result;
    __asm__("vsub.xyzw %0,%1,%2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=&j"(one) : "0"(d));
    __asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "+j"(d));
    __asm__("mtc1 %1,%0" : "=f"(result) : "r"(d));
    return result;
}
void func_0023B3A8(Node *p)
{
    Node *top;
    Stats *attached;
    if (!(p->flags & (3UL << 32))) return;
    top = p;
    attached = p->stats;
    if (!attached) {
        do {
            Node *next = top->parent;
            if (!next || ((long)(top->state << 8) >> 60) == 1) {
                Stats *s = func_0011E118(D_00479A48);
                top->stats = s;
                p->stats = s;
                s->origin = &top->reference->pos;
                ++p->stats->count;
                p->stats->scale = p->scale;
                p->stats->owner = p;
                if (top == p) goto position;
                attached = p->stats;
                goto count;
            }
            top = next;
            attached = top->stats;
        } while (!attached);
        p->stats = attached;
    }
count:
    ++attached->count;
position:
    {
        qword position = ((M4 *(*)(void *))p->vt[36].fn)((char *)p + p->vt[36].d)->d;
        float radius = p->radius + Distance(position, *p->stats->origin);
        if (p->flags & (1UL << 32)) {
            if (p->stats->low < radius) p->stats->low = radius;
        }
        if (p->flags & (1UL << 33)) {
            if (p->stats->high < radius) p->stats->high = radius;
        }
    }
}
