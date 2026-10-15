// Advance timed entity events using the original Sly 3 owner and resource layouts, checking idle flags and event timestamps.
// Reference algorithm: src/hand/func_001FDEC8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31
typedef unsigned long ulong;
struct X { char pad[0x44]; int n40; char pad2[0x5A - 0x48]; short n4E; unsigned short f50; unsigned short n52;  struct S *ps; char pad4[0x68 - 0x64]; ulong ul68; };
struct Ent { short h0; short pad; int n4; };
struct S { char pad[0x50]; float f50; int n54; struct Ent *a58; };
struct P { char pad[0x210]; struct X *r200; char pad2[0x258 - 0x214]; int n244; float f248; float f24C; };
extern float D_0036BBDC;
void func_00248740(struct P *);
void func_002480C8(struct P *, struct Ent *);
void func_00247EC8(struct P *p)
{
    struct X *x = p->r200;
    struct S *ps;
    int f;
    if (!x) return;
    {
        int g = x->n52 || (x->f50 & 1);
        if (g) return;
    }
    if (x->n4E > 0) return;
    ps = x->ps;
    p->f24C += D_0036BBDC;
    f = 0;
    if (!x->n40) {
        f = x->n52 || (x->f50 & 1);
        f ^= 1;
    }
    if (f) {
        if (0.0f < (float)p->r200->ul68 / 294912000.0f || ps->f50 <= p->f24C) func_00248740(p);
        return;
    }
    while (p->n244 < ps->n54) {
        struct Ent *pe = &ps->a58[p->n244];
        float d = (float)pe->h0 * 0.016666668f;
        if ((float)p->r200->ul68 / 294912000.0f < p->f248 + d) return;
        func_002480C8(p, pe);
        p->f248 += d;
        p->n244++;
    }
}
