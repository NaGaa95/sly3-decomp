// SLY3_CFLAGS: -Os -G0
struct R { float g; int n; float g8; };
struct LM { float gMin; float gMax; };
struct S { char pad[0x3C]; unsigned int fl; char pad2[0x198 - 0x40]; float g198; float g19C; char pad3[0x41C - 0x1A0];
    struct LM lm; char pad4[0x468 - 0x424]; int n468; char pad5[8]; struct R r; float g480; float g484; float g488; float g48C; };
extern struct S *D_00468D04;
void func_001F3B50(struct S *p);
void func_001C9118(struct S *p, int n);
void func_00209EB0(struct S *p)
{
    unsigned int v;
    struct R *pr;
    func_001F3B50(p);
    D_00468D04 = p;
    {
        struct LM *plm = &p->lm;
        plm->gMin = -1.5f;
        plm->gMax = 1.0f;
    }
    p->g198 = 0.4f;
    p->g19C = 0.4f;
    p->n468 = 8;
    pr = &p->r;
    pr->g = __builtin_fabsf(p->lm.gMax - p->lm.gMin) * 0.33333334f;
    pr->g8 = 5.0f;
    pr->n = 0;
    p->g484 = -0.8f;
    p->g488 = -0.2f;
    p->g480 = -1.5f;
    p->g48C = -1.5f;
    func_001C9118(p, 1);
    v = p->fl;
    if ((v ^ 1) & 1) *(int *)v |= 0xA;
    else p->fl = v | 0xA;
}
