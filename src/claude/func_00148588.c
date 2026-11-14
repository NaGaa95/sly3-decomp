// SLY3_CFLAGS: -Os -G0
/* Port of Sly 2 src/hand/CalculateBlendAmrsg__FiiPviiP4MRSGPf.c (Sly 3 offsets).
   One function-scope `ab` (a non-local pseudo, so the add ties to the product register) and the
   loop counters shared as in the target (i: loops 1/2-inner/3, j: loop 2-outer/5). */
struct MRSG { float g0; float g4; };
struct X { char pad[0x64]; float g74; };
struct E { float w; struct X *px; };
struct P { char pad[0xB0]; int cb; int c; char *ab; };
float GModPositive__Fff(float, float);
void func_00148588(struct P *p, int ib, int c, struct MRSG *amrsg, float *pf)
{
    float gSum = 0.0f;
    int i;
    char *ab;
    int j;
    if (c == 0) {
        if (pf) {
            for (i = 0; i < p->c; i++) {
                struct E *pe;
            ab = p->ab;
            pe = (struct E *)(ab + i * p->cb);
                if (pe->w != 0.0f)
                    gSum += pe->px->g74 * pe->w;
            }
            *pf = gSum;
        }
        return;
    }
    for (j = 0; j < c; j++) {
        amrsg[j].g4 = 0.0f;
        for (i = 0; i < p->c; i++) {
            struct E *pe;
            ab = p->ab;
            pe = (struct E *)(ab + i * p->cb);
            if (pe->w != 0.0f)
                amrsg[j].g4 += ((struct MRSG *)((char *)pe + ib))[j].g4 * pe->w;
        }
        gSum += amrsg[j].g4;
    }
    {
        int fFirst = 1;
        float gAvg, gFirst;
        for (i = 0; i < p->c; i++) {
            struct E *pe;
            ab = p->ab;
            pe = (struct E *)(ab + i * p->cb);
            if (pe->w != 0.0f) {
                float *pg = (float *)((char *)pe + ib);
                if (fFirst) {
                    fFirst = 0;
                    gAvg = *pg / pe->px->g74;
                    gFirst = gAvg;
                } else {
                    float d = *pg / pe->px->g74 - gFirst;
                    if (d <= -0.5f)
                        d += 1.0f;
                    else if (0.5f < d)
                        d -= 1.0f;
                    gAvg += d * pe->w;
                }
            }
        }
        amrsg[0].g0 = GModPositive__Fff(gAvg, 1.0f) * gSum;
    }
    for (j = 1; j < c; j++) {
        float g = amrsg[j - 1].g0 + amrsg[j - 1].g4;
        amrsg[j].g0 = g;
        if (gSum <= g)
            amrsg[j].g0 = g - gSum;
    }
    if (pf)
        *pf = gSum;
}
