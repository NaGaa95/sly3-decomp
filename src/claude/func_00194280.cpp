// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
typedef unsigned int uint;
enum UPK { UPK_V4_16 = 13 };
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
    void AddVifMscal(void *pv);
    void AddVifFlusha();
    void UnpackHelper(UPK upk, int c, int iqw, int *pcb, uint **ppun);
};
// VU1 microcode entry point (absolute VU address).
extern "C" {
extern char D_00003638[];
extern char D_002C4BF0[], D_002C8C08[];
void func_00182D60(VIFS *pvifs, void *pvStart, void *pvEnd);
void *memset(void *, int, unsigned int);
}
extern "C" void func_00194280(void *a, void *b, VIFS *pvifs)
{
    uint *pun;
    func_00182D60(pvifs, D_002C4BF0, D_002C8C08);
    pvifs->AddDmaCnt();
    pvifs->UnpackHelper(UPK_V4_16, 11, 12, 0, &pun);
    memset(pun, 0, 0x58);
    pvifs->AddVifMscal(D_00003638);
    pvifs->EndDmaCnt();
}
