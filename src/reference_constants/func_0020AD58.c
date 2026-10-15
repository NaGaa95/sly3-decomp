// Reference algorithm: src/hand/func_00153760.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct LM { float gMin; float gMax; } LM;
struct S { char pad[0x41C]; LM lm; int i23C; float ag[16]; int c280; };
float func_0011EE68(LM *plm, float g);
static inline int Max(int a, int b) { return a < b ? b : a; }
float func_0020AD58(struct S *p)
{
    float sum;
    int i, iMin;
    if (p->c280 <= 0)
        return 0.0f;
    sum = 0.0f;
    iMin = Max(p->i23C - p->c280, 0);
    for (i = p->i23C - 1; i >= iMin; i--)
        sum += p->ag[i];
    return func_0011EE68(&p->lm, sum / p->c280);
}
