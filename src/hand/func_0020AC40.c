// Modulate negative input through a clamped polynomial, retain up to 16 samples by shifting a full buffer, clamp the new sample, and notify the updated aggregate.
// Reference algorithm: src/hand/func_00153640.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef struct LM { float gMin; float gMax; } LM;
extern char D_0036BD20[];
extern char D_0036C700[];
extern float D_00325920[3];
extern LM D_00341FF0;
struct S { char pad[0x41C]; LM lm; int c; float ag[16]; float g280; float g284; };
float func_00171C98(void *p);
float func_0011EE68(LM *plm, float g);
float func_0020AD58(struct S *p);
void func_001854C8(void *p, int n, void *q);
void *func_00291F38(void *dst, void *src, int cb);
static inline float GClampLm(LM *plm, float g)
{
    if (g < plm->gMin)
        return plm->gMin;
    if (plm->gMax < g)
        return plm->gMax;
    return g;
}
static inline float GLim(LM *plm, float g)
{
    if (g < plm->gMin)
        g = plm->gMin;
    else if (plm->gMax < g)
        g = plm->gMax;
    return g;
}
static inline float GClamp(float g, float gMin, float gMax)
{
    if (g < gMin)
        return gMin;
    if (gMax < g)
        return gMax;
    return g;
}
void func_0020AC40(struct S *p, int a, int b, float g)
{
    float *pg;
    if (g < 0.0f) {
        float t = func_00171C98(D_0036BD20);
        g *= GClamp(D_00325920[0] + t * (D_00325920[1] + t * D_00325920[2]), D_00341FF0.gMin, D_00341FF0.gMax);
    }
    if (p->c == 16) {
        func_00291F38(&p->ag[0], &p->ag[1], 15 * sizeof(float));
        pg = &p->ag[p->c - 1];
    } else {
        pg = &p->ag[p->c++];
    }
    *pg = func_0011EE68(&p->lm, g);
    p->g284 = func_0020AD58(p);
    func_001854C8(D_0036C700, 0x49, p);
}
