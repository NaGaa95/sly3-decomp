// Reference algorithm: src/hand/func_001E7410.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct X { char pad[0xD8]; int c; float *ag; };
extern float D_00326DBC;
void func_0022E148(struct X *p, int a, int b, float g);
float func_0022DD48(struct X *p, float g);
void func_0022EF30(struct X *p, float (*pfn)(float, void *), void *pv, int a, int b, float *pg, float *pgOut)
{
    int i;
    float gBest = 0.0f;
    float dMin = D_00326DBC;
    for (i = 0; i < p->c; i++) {
        float g = p->ag[i];
        float d = pfn(g, pv);
        if (d < dMin) {
            dMin = d;
            gBest = g;
        }
    }
    if (a || b) func_0022E148(p, a, b, gBest);
    if (pg) *pg = gBest;
    if (pgOut) *pgOut = func_0022DD48(p, gBest);
}
