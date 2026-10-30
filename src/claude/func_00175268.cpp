// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// NEEDS symbols D_0036BD4C = 0x0036BD4C and D_0036BC88 = 0x0036BC88 (bss, not in symbol_addrs) -> then LINKED_MATCH.
// Draw the render list (Sly 2 counterpart: func_00157FA0, heavily changed in Sly 3).
typedef unsigned int uint;
typedef unsigned long ulong;
union QW { ulong aul[2]; uint aun[4]; float ag[4]; } __attribute__((aligned(16)));
enum UPK { UPK_S_32 = 0, UPK_V4_32 = 12 };
class DMAS {
public:
    unsigned char *m_pbMax, *m_ab; QW *m_pqwCnt; unsigned char *m_pb; int m_fPad, m_fEndPrim;
    void AddDmaCnt();
    void EndDmaCnt();
    void AddDmaCall(QW *pqw);
    void Flush();
    virtual void EndPrim(int n);
};
class VIFS : public DMAS {
public:
    uint m_unMask; int m_fCheckCnt;
    void AddVifUnpack(UPK upk, int c, void *pv, int iqw);
    void AddVifDirect(int cqw, QW *pqw, int fInt);
    void AddVifBaseOffset(int base, int offset);
};
struct ALLOCREQ { int cb; int cbAlign; };
class CTX {
    int storage[4];
public:
    CTX() __asm__("__3CTX");
    ~CTX() __asm__("_$_3CTX");
};
struct RPL { int k; float z; uint a8; uint aC; };
typedef void (*PFNRPL)(int k, int kOther, VIFS *pvifs);
struct RPLK { PFNRPL pfnBegin; PFNRPL pfnEnd; };
struct FRM { unsigned char pad[0x24]; QW *pqw24; unsigned char pad28[0x30 - 0x28]; int grf30; unsigned char pad34[0x100 - 0x34]; QW aqw100[1]; };
struct GAMEW { unsigned char pad[0x3EB8]; int c3EB8; void *a3EBC[1]; };
struct BGW { unsigned char pad[0xD8]; int fD8; };
extern "C" {
extern GAMEW D_00475480;
extern RPL D_00447B00[];
extern RPL *D_00468D00;
extern VIFS D_0036C308;
extern DMAS D_0036C2E0;
extern FRM *D_0036C328;
extern struct DBEC { int grf; } D_0036DBEC;
extern QW D_0036E340[];
extern int D_0036DCAC;
extern QW D_0036DCB0[];
extern int D_0036BD4C;
extern QW D_0036BC88[];
extern BGW D_0036BC10;
void func_00167D50(void *p);
void *PvAllocSlot(ALLOCREQ *req) __asm__("PvAllocSlot__FP8ALLOCREQ");
int func_00174CE8(int c, int cMax, RPL *arpl, RPL **aprpl, void *pv1, void *pv2);
int func_00175008(int k);
int func_00175070(int k);
RPLK *func_001750E8(int k);
RPLK *func_00175240(int k);
void func_002340B8(BGW *p, int n);
}
static inline ALLOCREQ *Request(ALLOCREQ *req, int cb, int cbAlign)
{
    req->cb = cb;
    req->cbAlign = cbAlign;
    return req;
}
extern "C" void func_00175268(void)
{
    int i;
    for (i = 0; i < D_00475480.c3EB8; i++)
        func_00167D50(D_00475480.a3EBC[i]);
    CTX ctx;
    ALLOCREQ req;
    RPL **aprpl = (RPL **)PvAllocSlot(Request(&req, 0x8000, 0x10));
    void *pv1 = PvAllocSlot(Request(&req, 0x380, 0x10));
    void *pv2 = PvAllocSlot(Request(&req, 0x380, 0x10));
    int c = func_00174CE8(D_00468D00 - D_00447B00, 0x2000, D_00447B00, aprpl, pv1, pv2);
    {
        QW *pqw = (QW *)D_0036C308.m_pb;
        D_0036C328->pqw24 = pqw;
    }
    if ((D_0036DBEC.grf >> 1) & 1)
        D_0036C308.AddDmaCall(D_0036C328->aqw100);
    else
        D_0036C308.AddDmaCall(D_0036E340);
    D_0036C308.AddDmaCnt();
    if (D_0036C328->grf30 & 4)
        D_0036C308.AddVifDirect(D_0036DCAC, D_0036DCB0, 0);
    D_0036C308.AddVifBaseOffset(0, 0);
    D_0036C308.AddVifUnpack(UPK_S_32, 1, &D_0036BD4C, 0xF);
    D_0036BD4C = 0;
    D_0036C308.AddVifUnpack(UPK_V4_32, 1, D_0036BC88, 0xB);
    D_0036C308.AddVifBaseOffset(0x34, 0x1E6);
    D_0036C308.EndDmaCnt();
    int kPrev = -1;
    for (int j = 0; j < c; j++) {
        RPL *prpl = aprpl[j];
        int k = prpl->k;
        if (k != kPrev) {
            int g0 = func_00175008(kPrev);
            int g1 = func_00175008(k);
            RPLK *prplk = func_001750E8(g0);
            if (prplk)
                prplk->pfnEnd(kPrev, k, &D_0036C308);
            int h0 = func_00175070(kPrev);
            int h1 = func_00175070(k);
            if (h1 != h0) {
                prplk = func_00175240(h0);
                if (prplk && prplk->pfnEnd)
                    prplk->pfnEnd(kPrev, k, &D_0036C308);
                prplk = func_00175240(h1);
                if (prplk)
                    prplk->pfnBegin(k, kPrev, &D_0036C308);
            }
            prplk = func_001750E8(g1);
            if (prplk)
                prplk->pfnBegin(k, kPrev, &D_0036C308);
            kPrev = k;
        }
        if (prpl->a8) {
            *(ulong *)D_0036C308.m_pb = ((ulong)prpl->a8 << 32) | 0x50000000;
            D_0036C308.m_pb += 0x10;
        }
        if (prpl->aC) {
            *(ulong *)D_0036C308.m_pb = ((ulong)prpl->aC << 32) | 0x50000000;
            D_0036C308.m_pb += 0x10;
        }
    }
    {
        RPLK *prplk = func_001750E8(func_00175008(kPrev));
        if (prplk)
            prplk->pfnEnd(kPrev, -1, &D_0036C308);
        prplk = func_00175240(func_00175070(kPrev));
        if (prplk && prplk->pfnEnd)
            prplk->pfnEnd(kPrev, -1, &D_0036C308);
    }
    D_00468D00 = 0;
    D_0036C2E0.Flush();
    D_0036C308.Flush();
    if (D_0036BC10.fD8) {
        D_0036BC10.fD8 = 0;
        func_002340B8(&D_0036BC10, 0);
    }
}
