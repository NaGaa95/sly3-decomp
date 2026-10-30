// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef struct { qword a, b, c, d; float t; int pad[3]; qword e; } HIT;
static const float s_gMax = 3.40282347e+38f;
int func_00164A10(void *p, qword a, qword b, int c, HIT *ahit);
void *func_00165000(int grf, qword a, qword b, int n, void **ap, HIT *phit)
{
    float gBest = s_gMax;
    void *pBest = 0;
    int i;
    for (i = 0; i < n; i++) {
        HIT ahit[2];
        void *p = ap[i];
        int c = func_00164A10(p, a, b, 2, ahit);
        int j = 0;
        if (c > 0 && ahit[0].t == 0.0f)
            j = grf & 1;
        if (j < c && ahit[j].t < gBest) {
            gBest = ahit[j].t;
            pBest = p;
            if (phit)
                *phit = ahit[j];
        }
    }
    return pBest;

}
