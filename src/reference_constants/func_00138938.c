// Reference algorithm: src/hand/func_001317D8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31
struct Q { char pad[0x64]; float tMax; };
struct P { int pad[5]; struct Q *pq; char pad1[0x3C - 0x18]; int grf; char pad2[0x44 - 0x40]; float g44; };
float func_002A4188(float a, float b);
float func_0011EDB8(float a, float b);
static __inline__ void PingPong(struct P *p, float *pt, float *pdt, float tMax, float t2)
{
    *pdt = __builtin_fabsf(*pdt);
    p->g44 = __builtin_fabsf(p->g44);
    if (tMax <= *pt) {
        *pt = t2 - *pt;
        *pdt = -*pdt;
        p->g44 = -p->g44;
    }
}
int func_00138938(struct P *p, float *pt, float *pdt)
{
    float tMax = p->pq->tMax;
    float t = *pt;
    int f = 0;
    if (tMax <= t) {
        if (0.0f < *pdt)
            f = 1;
        if (p->grf & 8) {
            *pt = func_002A4188(t, tMax);
        } else if (p->grf & 0x10) {
            float t2 = tMax + tMax;
            *pt = func_002A4188(t, t2);
            PingPong(p, pt, pdt, tMax, t2);
        } else {
            *pt = tMax;
            *pdt = 0.0f < *pdt ? 0.0f : *pdt;
        }
    } else if (t < 0.0f) {
        if (*pdt < 0.0f)
            f = 1;
        if (p->grf & 8) {
            *pt = func_0011EDB8(t, tMax);
        } else if (p->grf & 0x10) {
            float t2 = tMax + tMax;
            *pt = func_002A4188(-t, t2);
            PingPong(p, pt, pdt, tMax, t2);
        } else {
            *pt = 0.0f;
            *pdt = *pdt < 0.0f ? 0.0f : *pdt;
        }
    }
    return f;
}
