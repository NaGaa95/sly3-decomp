// Reference algorithm: src/hand/func_0014D0B8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef unsigned long ulong;
struct CLOCK {
    float t; float dt; float rDt; float rDtReal; float dtReal; float tReal; char pad[0x24 - 0x18]; float r24;
    char pad2[0x40 - 0x28]; float t3C; float dt40; ulong tick;
};
extern char D_0036C700[];
ulong func_001655B0(struct CLOCK *p);
void func_00185088(void *p);
static __inline__ float GClamp(float g, float gMin, float gMax)
{
    float r;
    if (g < gMin) r = gMin;
    else if (gMax < g) r = gMax;
    else r = g;
    return r;
}
void func_00165430(struct CLOCK *p, int fPaused)
{
    ulong tick = func_001655B0(p);
    float dt = GClamp((float)(tick - p->tick) * 3.3908420e-9f, 1.0f / 60.0f, 1.0f / 30.0f);
    p->dtReal = dt * p->rDtReal;
    p->tReal += p->dtReal;
    {
    float dt2 = dt * p->r24;
    p->dt40 = dt2;
    if (!fPaused) {
        p->dt = dt2 * p->rDt;
        p->t += p->dt;
        func_00185088(D_0036C700);
    }
    }
    p->tick = tick;
    p->t3C += p->dt40;
}
