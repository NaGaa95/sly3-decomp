// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sort compare for candidate entries (cf. Sly 2 src/hand/func_0020A168.c); the 2nd vtable lookup is hoisted above the first distance (zero-insn asm keeps vt live).
typedef int qword __attribute__((mode(TI)));
struct XF { char pad[0x30]; qword pos; };
struct VTE { short delta; short pad; struct XF *(*method)(void *); };
struct LO { char pad[0xC]; struct VTE *vt; };
struct K { char pad[0x40]; int n40; };
struct E2 { char pad[0x14]; struct K *pk; char pad2[0x20 - 0x18]; qword pos; char pad3[0x4C - 0x30]; float f4C; char pad4[4]; int n54; char pad5[0x60 - 0x58]; };
static inline float Dist2(qword a, qword *pq)
{
    qword d, r, t, g;
    float f;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(*pq));
    __asm__("vmul.xyz %0, %0, %0\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(r), "=&j"(t) : "0"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(r));
    __asm__("mtc1 %1, %0" : "=f"(f) : "r"(g));
    return f;
}
int func_00255C38(struct LO *p, struct E2 *a, struct E2 *b)
{
    int n;
    float d, d2;
    struct XF *x;
    struct VTE *vt;
    n = a->pk->n40 - b->pk->n40;
    if (n)
        return n;
    n = b->n54 - a->n54;
    if (n)
        return n;
    if (a->f4C > b->f4C)
        return -1;
    if (a->f4C < b->f4C)
        return 1;
    x = p->vt[36].method((char *)p + p->vt[36].delta);
    vt = p->vt;
    __asm__("" : : "r"(vt));
    d = Dist2(x->pos, &a->pos);
    x = vt[36].method((char *)p + vt[36].delta);
    d2 = Dist2(x->pos, &b->pos);
    if (d < d2)
        return -1;
    if (d2 > d)
        return 1;
    return a - b;
}
