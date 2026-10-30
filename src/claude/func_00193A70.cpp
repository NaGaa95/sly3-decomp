// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Adapted from the Sly 2 decomp (func_0016DA48): build the screen-fade VIF/GIF packet.
typedef unsigned int uint;
typedef unsigned long ulong;
union QW { ulong aul[2]; uint aun[4]; float ag[4]; } __attribute__((aligned(16)));
enum UPK { UPK_V2_16 = 5, UPK_V4_32 = 12 };
class DMAS {
public:
    unsigned char *m_pbMax, *m_ab; QW *m_pqwCnt; unsigned char *m_pb; int m_fPad, m_fEndPrim;
    void AllocStatic(int cqw, QW *aqw);
    void AddDmaCnt();
    void EndDmaCnt();
    virtual void EndPrim(int n);
};
class GIFS : public DMAS {
public:
    QW *m_pqwPrim; uint m_creg; uint m_cregAll;
    GIFS();
    virtual void EndPrim(int fEOP);
    void AddPrimPack(int prim, int creg, ulong regs);
    void PackAD(long a, long d);
    void AddPrimList(int creg, ulong regs);
    void ListXYZ(int x, int y, int z);
};
class VIFS : public DMAS {
public:
    uint m_unMask; int m_fCheckCnt;
    void AddVifMscal(void *pv);
    void AddVifFlusha();
    void UnpackHelper(UPK upk, int c, int iqw, int *pcb, uint **ppun);
    void AddVifUnpack(UPK upk, int c, void *pv, int iqw);
};
struct RECT;
extern "C" {
extern char D_00001B58[];
extern char D_002C2640[], D_002C45A8[];
extern int D_0036DBD0[2];
extern struct SCREEN { int x0; int x4; int x8; } D_0036DBE0;
void func_00182D60(VIFS *pvifs, void *pvStart, void *pvEnd);
void *func_001750B0(void *p);
int func_00175008(void *p);
void func_00193638(int n, GIFS *pgifs, short **pps);
void func_00193668(GIFS *pgifs, uint grf, void *pv, short **pps);
int func_002BC640(struct SCREEN *p, int n);
int func_002BC648(struct SCREEN *p, int n);
void func_00193A70(void *pA, void *pB, VIFS *pvifs);
}
void func_00193A70(void *pA, void *pB, VIFS *pvifs)
{
    char *base = (char *)func_001750B0(pA);
    int n1 = func_00175008(pA);
    int n2 = func_00175008(pB);
    func_00182D60(pvifs, D_002C2640, D_002C45A8);
    pvifs->AddDmaCnt();
    uint *pun;
    pvifs->UnpackHelper(UPK_V2_16, 9, 0x1B, 0, &pun);
    short *ps = (short *)pun;
    GIFS gifs;
    QW aqw[0x100];
    gifs.AllocStatic(0x100, aqw);
    if (n2 != 6)
        func_00193668(&gifs, 0x299, base + 0x160, &ps);
    gifs.AddPrimPack(0, 1, 0xE);
    func_00193638(0, &gifs, &ps);
    if (n1 == 6 || n2 != 6)
        gifs.PackAD(0x4C, 0xFFFF00FF00000000L);
    else
        gifs.PackAD(0x4C, 0xFFFF80FF00000000L);
    func_00193638(0, &gifs, &ps);
    if (n1 == 6 || n2 != 6)
        gifs.PackAD(0x4D, 0xFFFF00FF00000000L);
    else
        gifs.PackAD(0x4D, 0xFFFF80FF00000000L);
    gifs.PackAD(0x46, 0);
    gifs.PackAD(0x48, 0x31001);
    gifs.PackAD(0x45, 0);
    gifs.PackAD(0x19, 0);
    if (n1 == 6)
        gifs.PackAD(1, 0x100007E00L);
    else
        gifs.PackAD(1, 0x100003E00L);
    gifs.PackAD(0, 0x206);
    gifs.AddPrimList(2, 0x55);
    for (int x = 0; x < func_002BC640(&D_0036DBE0, D_0036DBE0.x4); x += 0x20) {
        gifs.ListXYZ(x << 4, 0, 0);
        gifs.ListXYZ((x + 0x20) << 4, func_002BC648(&D_0036DBE0, D_0036DBE0.x8) << 4, 0);
    }
    if (n1 == 7 && n2 == 6) {
        gifs.AddPrimPack(0, 1, 0xE);
        func_00193638(0, &gifs, &ps);
        gifs.PackAD(0x4C, 0xFFFF00FF00000000L);
    }
    gifs.EndPrim(1);
    func_00193638(-1, &gifs, &ps);
    pvifs->AddVifUnpack(UPK_V4_32, (uint)(gifs.m_pb - gifs.m_ab) >> 4, gifs.m_ab, 0x24);
    pvifs->AddVifFlusha();
    pvifs->AddVifMscal(D_00001B58);
    pvifs->AddVifFlusha();
    pvifs->EndDmaCnt();
    D_0036DBD0[n1 == 7 ? 1 : 0] = 1;
}
