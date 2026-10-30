// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Adapted from the Sly 2 decomp (func_0016DD58): build the screen-effect VIF and GIF packets.
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
    void ListUV(int u, int v);
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
extern "C" {
extern char D_00001D30[];
extern int D_0036DBD0[2];
extern ulong D_0036BCE0;
extern struct SCREEN { int x0; int x4; int x8; } D_0036DBE0;
void *func_001750B0(void *p);
int func_00175008(void *p);
void func_00193638(int n, GIFS *pgifs, short **pps);
void func_00193668(GIFS *pgifs, uint grf, void *pv, short **pps);
int func_002BC640(struct SCREEN *p, int n);
int func_002BC648(struct SCREEN *p, int n);
void func_00193DF8(void *pA, void *pB, VIFS *pvifs);
}
void func_00193DF8(void *pA, void *pB, VIFS *pvifs)
{
    char *base = (char *)func_001750B0(pA);
    int mode = func_00175008(pB);
    pvifs->AddDmaCnt();
    uint *pun;
    pvifs->UnpackHelper(UPK_V2_16, 9, 0x1B, 0, &pun);
    short *ps = (short *)pun;
    GIFS gifs;
    QW aqw[0x200];
    gifs.AllocStatic(0x200, aqw);
    if (func_00175008(pB) != 7) {
        if (D_0036DBD0[1]) {
            gifs.AddPrimPack(0, 1, 0xE);
            func_00193638(0, &gifs, &ps);
            gifs.PackAD(0x4D, 0xFFFFFEFF00000000L);
            gifs.PackAD(0x48, 0x31001L);
            gifs.PackAD(0x43, 0x2000000A9L);
            gifs.PackAD(1, 0x100000000L);
            gifs.PackAD(0, 0x246L);
            gifs.AddPrimList(2, 0x55UL);
            for (int x = 0; x < func_002BC640(&D_0036DBE0, D_0036DBE0.x4); x += 0x20) {
                gifs.ListXYZ(x << 4, 0, 0);
                gifs.ListXYZ((x + 0x20) << 4, func_002BC648(&D_0036DBE0, D_0036DBE0.x8) << 4, 0);
            }
        }
        func_00193668(&gifs, 0x810095, base + 0x160, &ps);
        func_00193668(&gifs, 0x266, base + 0x160, &ps);
    }
    gifs.AddPrimPack(0, 1, 0xE);
    func_00193638(8, &gifs, &ps);
    gifs.PackAD(0x4C, 0);
    gifs.PackAD(0x46, 1);
    if (mode != 7) {
        func_00193638(8, &gifs, &ps);
        gifs.PackAD(0x4D, 0);
        func_00193638(2, &gifs, &ps);
        gifs.PackAD(7, 0x6A8000000L);
        gifs.PackAD(0x15, 1);
        gifs.PackAD(0x17, D_0036BCE0);
        gifs.PackAD(0x3F, 0);
        gifs.PackAD(0x48, 0x31001);
        gifs.PackAD(1, 0x180808080L);
        gifs.PackAD(0x43, 0x44);
        gifs.PackAD(0, 0x356);
        gifs.AddPrimList(4, 0x5353);
        for (int x = 0; x < func_002BC640(&D_0036DBE0, D_0036DBE0.x4); x += 0x20) {
            gifs.ListUV((x << 4) | 8, 8);
            gifs.ListXYZ(x << 4, 0, 0);
            gifs.ListUV(((x + 0x20) << 4) + 8, (func_002BC648(&D_0036DBE0, D_0036DBE0.x8) << 4) | 8);
            gifs.ListXYZ((x + 0x20) << 4, func_002BC648(&D_0036DBE0, D_0036DBE0.x8) << 4, 0);
        }
    }
    gifs.EndPrim(1);
    func_00193638(-1, &gifs, &ps);
    int count = (uint)(gifs.m_pb - gifs.m_ab) >> 4;
    if (count >= 0x100) {
        pvifs->AddVifUnpack(UPK_V4_32, 0xFF, gifs.m_ab, 0x24);
        pvifs->AddVifUnpack(UPK_V4_32, ((uint)(gifs.m_pb - gifs.m_ab) >> 4) - 0xFF, gifs.m_ab + 0xFF0, 0x123);
    } else
        pvifs->AddVifUnpack(UPK_V4_32, count, gifs.m_ab, 0x24);
    pvifs->AddVifFlusha();
    pvifs->AddVifMscal(D_00001D30);
    pvifs->AddVifFlusha();
    pvifs->EndDmaCnt();
    if (mode != 7) {
        D_0036DBD0[0] = 0;
        D_0036DBD0[1] = 0;
    }
}
