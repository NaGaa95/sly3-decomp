#include "heap_frame_api.h"
// Reference algorithm: src/hand/func_0011AD30.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct MSG {
    int cb;
    int nKind;
}
MSG;
typedef struct DL {
    void *pvFirst;
    void *pvLast;
    int ibDle;
}
DL;
typedef struct DLE {
    void *pvNext;
    void *pvPrev;
}
DLE;
typedef struct FRAME {
    int an[4];
}
FRAME;
typedef struct DZ {
    int nKind;
    int n4;
    float g8;
    float gC;
    float g10;
    int n14;
    float *ag;
    int n1C;
    DLE dle;
}
DZ;
typedef struct DZG {
    int cdzsMax;
    int cdzs;
    DZ *adzs;
    DL dlA;
    DL dlB;
    DL dlC;
    DL dlD;
    int n3C;
    void *pv40;
    void *pv44;
    void *pv48;
    void *pv4C;
}
DZG;
void *func_001D25B0(MSG *pmsg);
void func_001D2898(void *pvDst, void *pvSrc, unsigned int cb);
DZG *func_0011B290(DZG *pdzg, int cdzsMax);
void func_0011AF60(DL *pdl, void *pv);
void func_0011B968(DZG *pdzg);
static inline void *PvAllocMsg(MSG *pmsg, int cb, int nKind) {
    pmsg->cb = cb;
    pmsg->nKind = nKind;
    return func_001D25B0(pmsg);
}
void func_0011BA98(int c, float g, float *agA, float *agB, float *agX) {
    FRAME frame;
    DZG dzg;
    MSG msg;
    int i;
    func_001D2770(&frame);
    func_0011B290(&dzg, c);
    for (i = 0; i < c; i++) {
        DZ *pdz = &dzg.adzs[i];
        pdz->g8 = g;
        pdz->ag = (float *)PvAllocMsg(&msg, c * sizeof(float), 0x10);
        func_001D2898(pdz->ag, agA + i * c, c * sizeof(float));
        pdz->g10 = agB[i];
        func_0011AF60(&dzg.dlD, pdz);
    }
    dzg.cdzs = c;
    func_0011B968(&dzg);
    for (i = 0; i < c; i++) {
        agX[i] = dzg.adzs[i].gC;
    }
    func_001D2798(&frame, 2);
}
