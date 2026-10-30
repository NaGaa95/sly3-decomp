// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Port of Sly 2 src/hand/func_0014EA08.c (geometry refresh added before the query).
typedef int qword __attribute__((mode(TI)));
struct T { int a, b, c; };
struct OX { char pad[0xA4]; int k; };
struct Q { int pad[2]; int c; struct T *at; };
struct O { struct OX *p0; char pad[0x78 - 4]; struct Q q; char pad2[0xC0 - 0x88]; int k; };
struct HIT { char pad[0x40]; float g40; float g44; char pad2[0x18]; };
void func_0018B1E0(struct O *po);
int func_00119BE8(struct T *pBegin, struct T *pEnd, qword pos, qword dir, int c, struct HIT *ahit);
int func_00164D98(int c, struct HIT *ahit, int cNew, struct HIT *ahitNew, int cMax, struct HIT *ahitOut, int f);
int func_00166F08(int n, struct O **apo, qword pos, qword dir, float *pgMin, float *pgMax, float g)
{
    struct HIT ahit[0x40];
    int c = 0;
    int i;
    int j;
    float g0, g1;
    int f;
    for (i = 0; i < n; i++) {
        struct O *po = apo[i];
        struct Q *pq;
        int cNew;
        if (po->k != po->p0->k) func_0018B1E0(po);
        pq = &po->q;
        cNew = func_00119BE8(pq->at, pq->at + pq->c, pos, dir, 0x40 - c, &ahit[c]);
        if (cNew)
            c = func_00164D98(c, ahit, cNew, &ahit[c], 0x40, ahit, 0);
    }
    for (j = 0; !(f = c < j); j++) {
        if (j > 0)
            g0 = ahit[j - 1].g44;
        else
            g0 = 0.0f;
        if (j < c)
            g1 = ahit[j].g40;
        else
            g1 = 1.0f;
        if (g < g1 - g0)
            break;
    }
    if (f)
        return 0;
    if (pgMin)
        *pgMin = g0;
    if (pgMax)
        *pgMax = g1;
    return 1;
}
