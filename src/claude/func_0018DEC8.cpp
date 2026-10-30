// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
// Adapted from the Sly 2 decomp (func_00167FC0).
typedef unsigned int uint;
enum UPK { UPK_V4_32 = 12 };
union QW { uint aui[4]; float ag[4]; } __attribute__((aligned(16)));
class DMAS {
public:
    unsigned char *m_pbMax, *m_ab; void *m_pqwCnt; unsigned char *m_pb; int m_fPad, m_fEndPrim;
    void AddDmaCnt();
    void EndDmaCnt();
    virtual void EndPrim(int n);
};
class VIFS : public DMAS {
public:
    uint m_unMask; int m_fCheckCnt;
    void AddVifBaseOffset(int iqwBase, int diqwOffset);
    void AddVifFlusha();
    void UnpackHelper(UPK upk, int c, int iqw, int *pcb, uint **ppun);
};
struct X { char pad[0x110]; QW amat[3]; int f140[4]; int f150; };
struct G;
extern "C" {
extern G D_00475480;
// Microcode blob 0x2C4600..0x2C4BD8, addressed from the neighbouring symbols.
extern char D_002C45C0[];
extern char D_002C4BF0[];
void func_00182D60(VIFS *pvifs, void *pvStart, void *pvEnd);
int func_0017E208(G *pg, int kind, int n, int m, int c, void **apv);
void CopyAb(void *pvDst, void *pvSrc, unsigned int cb);
}
static inline int Min(int a, int b) { return a < b ? a : b; }
extern "C" void func_0018DEC8(void *a, void *b, VIFS *pvifs)
{
    X *apx[0x180];
    int i;
    X *px;
    int cActive = 0;
    func_00182D60(pvifs, D_002C45C0 + 0x40, D_002C4BF0 - 0x18);
    pvifs->AddDmaCnt();
    pvifs->AddVifFlusha();
    pvifs->AddVifBaseOffset(0x34, 0);
    int c = func_0017E208(&D_00475480, 0x505, 4, 0, 0x180, (void **)apx);
    for (i = 0; i < c; i++) {
        px = apx[i];
        if (!px->f150)
            cActive++;
    }
    if (cActive > 0x100)
        cActive = 0x100;
    uint *pun;
    pvifs->UnpackHelper(UPK_V4_32, 1, 0, 0, &pun);
    pun[0] = 1;
    pun[1] = cActive * 3 + 1;
    uint *pb = 0;
    int n = 0;
    int iEnd = 0;
    for (i = 0; i < c; i++) {
        px = apx[i];
        if (px->f150)
            continue;
        if (n >= iEnd) {
            iEnd = n + Min(cActive - n, 32);
            pvifs->UnpackHelper(UPK_V4_32, (iEnd - n) * 3, n * 3 + 1, 0, &pb);
        }
        CopyAb(pb, px->amat, 0x30);
        n++;
        pb = (uint *)((char *)pb + 0x30);
        if (n >= 0x100)
            break;
    }
    pvifs->EndDmaCnt();
}
