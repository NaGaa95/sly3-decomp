// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Adapted from Sly 2 src/hand/func_002020C8.c.
typedef int qword __attribute__((mode(TI)));
struct VE { short d; short pad; void *pf; };
struct XF { char pad[0x30]; qword pos; };
struct LO { char pad[0xC]; struct VE *vt; };
struct T { char pad[0x2F]; unsigned long b2F : 8; };
struct O { char pad[0xC]; struct VE *vt; char pad10[0xF0 - 0x10]; struct T *pt; float r; };
struct S { char pad[0x30]; int c; struct O *a[(0xA8 - 0x34) / 4]; void **pA8; };
struct LO *func_001F4A80(void *p);
void func_00241338(struct T *pt, float f);
void func_002412C8(struct T *pt, float f);
static inline qword Pos(void *p, struct VE *vt)
{
    return ((struct XF *(*)(void *))vt[36].pf)((char *)p + vt[36].d)->pos;
}
void func_0024BFB0(struct S *p)
{
    int i;
    struct LO *t = func_001F4A80(*p->pA8);
    for (i = 0; i < p->c; i++) {
        struct O *o = p->a[i];
        qword a, b, d;
        float f;
        if (!o->pt)
            continue;
        a = Pos(o, o->vt);
        __asm__("" : "=j"(a) : "0"(a)); /* zero-insn: keep a in a VU register */
        b = Pos(t, t->vt);
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
        __asm__("vmul.xy %0, %0, %0\n\tvaddy.x %0, %0, %0y\n\tvsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "+j"(d));
        __asm__("qmfc2.ni %0, %1" : "=r"(f) : "j"(d));
        if (o->r < f && !(o->pt->b2F & 1))
            func_00241338(o->pt, 0.25f);
        else if (f <= o->r && (o->pt->b2F & 1))
            func_002412C8(o->pt, 0.25f);
    }
}
