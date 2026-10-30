// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Adapted from the Sly 2 decomp (func_0016D6C8): add the fade-overlay GIF primitives.
typedef unsigned int uint;
typedef unsigned long ulong;
union QW { ulong aul[2]; uint aun[4]; float ag[4]; } __attribute__((aligned(16)));
class DMAS {
public:
    unsigned char *m_pbMax, *m_ab; QW *m_pqwCnt; unsigned char *m_pb; int m_fPad, m_fEndPrim;
    virtual void EndPrim(int n);
};
class GIFS : public DMAS {
public:
    QW *m_pqwPrim; uint m_creg; uint m_cregAll;
    virtual void EndPrim(int fEOP);
    void AddPrimPack(int prim, int creg, ulong regs);
    void PackAD(long a, long d);
    void AddPrimList(int creg, ulong regs);
    void ListUV(int u, int v);
    void ListXYZ(int x, int y, int z);
};
extern "C" {
extern struct SCREEN { int x0; int x4; int x8; } D_0036DBE0;
void func_00193638(int n, GIFS *pgifs, short **pps);
int func_002BC640(struct SCREEN *p, int n);
int func_002BC648(struct SCREEN *p, int n);
void func_00193668(GIFS *pgifs, uint grf, void *pv, short **pps);
}
void func_00193668(GIFS *pgifs, uint grf, void *pv, short **pps)
{
    pgifs->AddPrimPack(0x200, 1, 0xE);
    func_00193638((grf & 4) ? 4 : 5, pgifs, pps);
    if (grf & 0x200) {
        pgifs->PackAD(0x4D, 0x3FFF02000000L);
    } else if (grf & 0x100) {
        pgifs->PackAD(0x4D, 0xFFFFC00002000000L);
    } else {
        uint msk = (grf & 0x800000) ? 0x7FFFFFFF : 0xFFFFFFFF;
        if (grf & 0x400000) msk &= 0xFF7FFFFF;
        if (grf & 0x200000) msk &= 0xFFBFFFFF;
        if (grf & 0x100000) msk &= 0xFFDFFFFF;
        if (grf & 0x80000) msk &= 0xFFEFFFFF;
        if (grf & 0x40000) msk &= 0xFFF0FFFF;
        if (grf & 0x20000) msk &= 0xFFFF7FFF;
        if (grf & 0x10000) msk &= 0xFFFFBFFF;
        pgifs->PackAD(0x4D, ((ulong)msk << 32) | 0x2000000);
    }
    func_00193638((grf & 1) ? 6 : 7, pgifs, pps);
    pgifs->PackAD(7, 0xEA8200000L);
    pgifs->PackAD(0x15, 1);
    pgifs->PackAD(0x3F, 0);
    pgifs->PackAD(0x45, 0);
    pgifs->PackAD(0x19, 0);
    {
        int cx = func_002BC640(&D_0036DBE0, D_0036DBE0.x4);
        int cy = func_002BC648(&D_0036DBE0, D_0036DBE0.x8);
        pgifs->PackAD(0x41, ((long)(cx - 1) << 16) | ((long)(cy * 2 - 1) << 48));
    }
    pgifs->PackAD(0x48, 0x31001);
    pgifs->PackAD(0x43, 0x2A);
    pgifs->PackAD(0x3B, 0x8000000000L);
    pgifs->PackAD(1, 0x180808080L);
    pgifs->PackAD(0, 0x356);
    pgifs->AddPrimList(4, 0x5353);
    int x = (grf & 0x40) ? 0 : 8;
    int u = (grf & 0x10) ? 0 : 8;
    for (; x < func_002BC640(&D_0036DBE0, D_0036DBE0.x4); x += 0x10, u += 0x10) {
        pgifs->ListUV((u << 4) + 8, 8);
        pgifs->ListXYZ(x << 4, 0, 0);
        pgifs->ListUV(((u + 8) << 4) + 8, (func_002BC648(&D_0036DBE0, D_0036DBE0.x8) << 5) + 8);
        pgifs->ListXYZ((x + 8) << 4, func_002BC648(&D_0036DBE0, D_0036DBE0.x8) << 5, 0);
    }
    pgifs->AddPrimPack(0x200, 1, 0xE);
    {
        int cx = func_002BC640(&D_0036DBE0, D_0036DBE0.x4);
        int cy = func_002BC648(&D_0036DBE0, D_0036DBE0.x8);
        pgifs->PackAD(0x41, ((long)(cx - 1) << 16) | ((long)(cy - 1) << 48));
    }
}
