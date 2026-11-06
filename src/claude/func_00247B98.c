// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00247B98: pick the active one of three blend weights and renormalize them (cf. Sly 2 func_001FDC50 family).
struct REF { char pad[0x5C]; unsigned short flags; unsigned short state; };
struct COEF { float a, b, c; };
struct VTE { short delta; short pad; int (*pfn)(void *); };
struct PLAYER
{
    char pad0[0xC];
    struct VTE *vt;
    char pad10[0x508 - 0x10];
    int action;
    char pad50C[0x1108 - 0x50C];
    void *p1108;
    char pad110C[0x11A0 - 0x110C];
    int n11A0;
    char pad11A4[0x11C4 - 0x11A4];
    int state;
};
struct P
{
    char pad[0x5C];
    int modeA;
    int modeB;
    int sel;
    char pad68[0x10C - 0x68];
    float aw[3];
    struct COEF acoef[3];
    char pad13C[0x214 - 0x13C];
    int cref;
    struct REF *aref[8];
};
extern char D_00475480[];
extern float D_0036BBDC;
int func_001A9478(void *p, int n);
struct PLAYER *func_001F4AD0(void *p, int n);
int func_0013B500(void *p, int n);
int func_00172CE0(void *p);
float func_0011E598(float g, float gTarget, float dt, struct COEF *pcoef, float *pdg);
void func_00246190(struct REF *pref, int i, float g);

static inline float Sqrt(float f)
{
    float r;
    __asm__ __volatile__("sqrt.s %0,%1" : "=f"(r) : "f"(f));
    return r;
}

void func_00247B98(struct P *p)
{
    struct REF *pref;
    int i, j, k;
    float sum, sq;

    p->sel = 1;
    if (p->modeA)
        p->sel = 2;
    else if (p->modeB)
        p->sel = 0;
    else if (!func_001A9478(D_00475480, -1) && func_001F4AD0(D_00475480, 0) &&
             func_0013B500(func_001F4AD0(D_00475480, 0), 0x33))
    {
        struct PLAYER *pplayer = func_001F4AD0(D_00475480, 0);
        if (!pplayer->p1108 || func_00172CE0(pplayer->p1108) == -1)
        {
            switch (pplayer->state)
            {
            case 4:
                p->sel = 2;
                break;
            case 3:
                if (!pplayer->vt[0x6B].pfn((char *)pplayer + pplayer->vt[0x6B].delta))
                    p->sel = 0;
                break;
            default:
                if (pplayer->n11A0 != -1 && !pplayer->vt[0x6B].pfn((char *)pplayer + pplayer->vt[0x6B].delta))
                    p->sel = 0;
                else if (pplayer->action >= 0 && (pplayer->action < 3 || pplayer->action == 13))
                    p->sel = 0;
                break;
            }
        }
    }

    if (p->cref > 0)
        pref = ((struct REF **)&p->cref)[p->cref];
    else
        pref = 0;

    if (pref)
    {
        int fLocked = 0;
        if (pref->state || (pref->flags & 1))
            fLocked = 1;
        if (!fLocked)
            goto smooth;
    }
    p->aw[p->sel] = 1.0f;
    goto norm;
smooth:
    p->aw[p->sel] = func_0011E598(p->aw[p->sel], 1.0f, D_0036BBDC, &p->acoef[p->sel], 0);
norm:
    sum = 0.0f;
    sq = p->aw[p->sel] * p->aw[p->sel];
    for (i = 0; i < 3; i++)
        if (i != p->sel)
            sum += p->aw[i] * p->aw[i];
    if (sum < 0.0001f)
    {
        for (j = 0; j < 3; j++)
            p->aw[j] = (j == p->sel) ? 1.0f : 0.0f;
    }
    else
    {
        float gain = Sqrt((1.0f - sq) / sum);
        for (k = 0; k < 3; k++)
            if (k != p->sel)
                p->aw[k] *= gain;
    }
    if (pref)
    {
        func_00246190(pref, 0, p->aw[0]);
        func_00246190(pref, 1, p->aw[1]);
        func_00246190(pref, 2, p->aw[2]);
    }
}
