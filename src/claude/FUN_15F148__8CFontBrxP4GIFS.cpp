// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sly 2 reference: /home/claude/decomp src/auto/func_0015F148.c (same body).
struct QW;
struct DMAS {
    void EndDmaCnt();
    void AddDmaCnt();
    void AddDmaRefs(int c, QW *p);
};
struct GIFS : DMAS {};
struct FONTCACHE { char pad[0x2C]; int grf; };
extern "C" GIFS D_0036C2E0;
extern "C" FONTCACHE *D_0036C328;
class CFontBrx {
public:
    int FUN_15F148(GIFS *pgifs);
    int m_ifont;
    char pad[0x58 - 4];
    int c58; QW *p5C;
    char pad2[0xC0 - 0x60];
    int cC0; QW *pC4;
    int cC8; QW *pCC;
    char pad3[0x130 - 0xD0];
    int c130; QW *p134;
};
int CFontBrx::FUN_15F148(GIFS *pgifs)
{
    int fNew;
    if (pgifs == &D_0036C2E0) {
        int bit = 1 << m_ifont;
        int grf = D_0036C328->grf;
        fNew = (grf & bit) == 0;
        D_0036C328->grf = grf | bit;
    } else {
        fNew = 1;
    }
    if (fNew) {
        pgifs->EndDmaCnt();
        pgifs->AddDmaRefs(c58, p5C);
        pgifs->AddDmaRefs(cC0, pC4);
        if (cC8) {
            pgifs->AddDmaRefs(cC8, pCC);
            pgifs->AddDmaRefs(c130, p134);
        }
        pgifs->AddDmaCnt();
    }
    return fNew;
}
