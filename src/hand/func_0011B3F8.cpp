// Sly 2 reference: src/hand/ClearDzgSolution__FP3DZG.cpp.
// GNU declaration labels establish canonical Sly 3 symbols without executable assembly.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct DL { void *pvFirst; void *pvLast; int ibDle; };
struct DLE { void *pvNext; void *pvPrev; };
struct DZS {
    char pad0[0xC];
    float gC;
    float g10;
    char pad14[0xC];
    DLE dle;
};
struct DZG {
    int cdzsMax;
    int cdzs;
    DZS *adzs;
    DL dlA;
    DL dlB;
    DL dlC;
    DL dlD;
    int n3C;
};

extern "C" {
void func_0011AF40(DL *pdl) __asm__("func_0011AF40");
void func_0011AF50(DLE *pdle) __asm__("func_0011AF50");
void func_0011AF60(DL *pdl, void *pv) __asm__("func_0011AF60");
}

void ClearDzgSolution(DZG *pdzg) __asm__("func_0011B3F8");
void ClearDzgSolution(DZG *pdzg)
{
    int i;

    pdzg->n3C = 0;
    func_0011AF40(&pdzg->dlA);
    func_0011AF40(&pdzg->dlB);
    func_0011AF40(&pdzg->dlC);
    func_0011AF40(&pdzg->dlD);

    for (i = 0; i < pdzg->cdzs; i++) {
        DZS *pdzs = &pdzg->adzs[i];
        pdzs->gC = pdzs->g10 = 0.0f;
        func_0011AF50(&pdzs->dle);
        func_0011AF60(&pdzg->dlD, pdzs);
    }
}
