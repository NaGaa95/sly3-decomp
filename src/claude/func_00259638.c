// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// SLY3_ASFIX: engine-divfix1
// Fraction of the way along a looped path: (t - t0, wrapped by the loop length) / duration.
struct L { char pad[0x64]; float len; };
struct C { char pad[0x14]; struct L *pl; char pad2[0x1C - 0x18]; float t; };
struct S { char pad[0x24]; struct C *pc; };
float func_00259638(struct S *p, float *pv)
{
    struct C *c = p->pc;
    float t = c->t;
    if (t < pv[0])
        t += c->pl->len;
    t -= pv[0];
    return t / pv[1];
}
