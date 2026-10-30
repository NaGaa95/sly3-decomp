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
// VU1 microcode entry points (absolute VU addresses).
extern "C" {
extern char D_00003F90[], D_00003638[], D_00003AD0[];
// Microcode blob at 0x2C8C20..0x2CC778 has no symbol in symbol_addrs.txt; it is addressed relative to the
// nearest one (D_002C8C08). The second declaration is the same symbol under another C name so gcc does not
// derive the end address from the start address (the original loads both with separate lui/addiu).
extern char D_002C8C08[];
extern char D_002C8C08_b[] __asm__("D_002C8C08");
void func_00182D60(VIFS *pvifs, void *pvStart, void *pvEnd);
void *memset(void *, int, unsigned int);
}
extern "C" void func_00194308(void *a, void *b, VIFS *pvifs)
{
    uint *pun;
    pvifs->AddDmaCnt();
    pvifs->UnpackHelper(UPK_V4_16, 11, 12, 0, &pun);
    memset(pun, 0, 0x58);
    pvifs->AddVifMscal(D_00003F90);
    pvifs->AddVifFlusha();
    pvifs->EndDmaCnt();
}
extern "C" void func_00194380(void *a, void *b, VIFS *pvifs)
{
    uint *pun;
    func_00182D60(pvifs, D_002C8C08 + 0x18 /* 0x2C8C20 */, D_002C8C08_b + 0x3B70 /* 0x2CC778 */);
    pvifs->AddDmaCnt();
    pvifs->UnpackHelper(UPK_V4_16, 11, 12, 0, &pun);
    memset(pun, 0, 0x58);
    pvifs->AddVifMscal(D_00003638);
    pvifs->EndDmaCnt();
}
extern "C" void func_00194408(void *a, void *b, VIFS *pvifs)
{
    uint *pun;
    pvifs->AddDmaCnt();
    pvifs->UnpackHelper(UPK_V4_16, 11, 12, 0, &pun);
    memset(pun, 0, 0x58);
    pvifs->AddVifMscal(D_00003AD0);
    pvifs->AddVifFlusha();
    pvifs->EndDmaCnt();
}
