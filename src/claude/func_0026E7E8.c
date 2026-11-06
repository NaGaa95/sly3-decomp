// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Adapted from Sly 2 src/hand/func_0021C1C8.c.
typedef int qword __attribute__((mode(TI)));
struct M { qword r[4]; };
struct T { float t; float g; float length; int pad; struct M m; };
struct VE { short d; short pad; void *pf; };
struct XF { struct M m; };
struct LO { char pad[0xC]; struct VE *vt; };
struct S {
    char pad[0xC]; struct VE *vt; char pad10[0x104 - 0x10]; float g;
    char pad108[0x134 - 0x108]; int state; float timer; int count; struct T *array; int index; int idle;
    char pad14c[0x160 - 0x14C]; struct LO *follow; float rate; float distance;
    char pad16c[4]; qword previous;
};
extern struct CLOCK { float t; float dt; } g_clock;
void func_0023C970(struct S *);
void func_0026EC80(struct S *, qword);
static inline struct XF *Xf(void *p, struct VE *vt)
{
    return ((struct XF *(*)(void *))vt[36].pf)((char *)p + vt[36].d);
}
static inline qword VSub(qword a, qword b)
{
    qword d;
    __asm__("vsub.xyzw %0,%1,%2" : "=j"(d) : "j"(a), "j"(b));
    return d;
}
static inline qword Dot(qword d) {
    qword one;
    __asm__("vmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "+j"(d), "=j"(one));
    return d;
}
static inline float Sqrt(qword d) {
    float f;
    __asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q" : "+j"(d));
    __asm__("qmfc2.ni %0,%1" : "=r"(f) : "j"(d));
    return f;
}
void func_0026E7E8(struct S *p)
{
    func_0023C970(p);
    if (!p->state) {
        p->timer += g_clock.dt;
        if (0.016666668f <= p->timer) {
            struct T *e;
            p->timer = 0.0f;
            e = &p->array[p->index];
            p->index = (p->index + 1) % p->count;
            e->t = g_clock.t;
            e->g = p->g;
            e->m = Xf(p, p->vt)->m;
            if (p->g <= 0.0f)
                p->idle++;
            else
                p->idle = 0;
            if (p->follow) {
                qword pos;
                float length;
                if (p->g == 0.0f)
                    p->distance = -4.0f;
                pos = Xf(p->follow, p->follow->vt)->m.r[3];
                {
                    float rate = p->rate;
                    qword d = VSub(p->previous, pos);
                    float dist = p->distance;
                    d = Dot(d);
                    p->previous = pos;
                    length = Sqrt(d);
                    p->distance = dist + length / rate;
                }
                e->length = p->distance;
            }
        }
        func_0026EC80(p, Xf(p, p->vt)->m.r[3]);
    }
}
