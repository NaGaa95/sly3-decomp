// Sly 2 reference: src/hand/WriteTftPchz__FP3TFTP5OSTRMPc.cpp.
// GNU declaration labels establish canonical Sly 3 symbols without executable assembly.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct TFT { int fLeft; int x4; int x8; int xC; int fZero; int fPrec0; int cchWidth; int cchPrec; int cbits; char pad24[8]; unsigned char chConv; };
class OSTRM {
public:
    int CbWrite(void *pv, int cb) __asm__("func_0025A2D0");
};
extern "C" int func_002715F8(char *pch) __asm__("func_002715F8");
extern "C" char D_00328D10[];
static inline void WritePad(OSTRM *postrm, char ch, int c)
{
    char b = ch;
    while (c-- > 0)
        if (postrm->CbWrite(&b, 1) != 1)
            break;
}
void WriteTftPchz(TFT *ptft, OSTRM *postrm, char *pchz) __asm__("func_0026FF90");
void WriteTftPchz(TFT *ptft, OSTRM *postrm, char *pchz)
{
    int cch;
    int cchLeft;
    int cchRight;
    char ch;
    if (!pchz)
        pchz = D_00328D10;
    cch = func_002715F8(pchz);
    cchRight = 0;
    cchLeft = 0;
    if (ptft->cchPrec && ptft->cchPrec < cch)
        cch = ptft->cchPrec;
    else if (ptft->fPrec0)
        cch = 0;
    if (cch < ptft->cchWidth) {
        ch = ptft->fZero ? '0' : ' ';
        int cchPad = ptft->cchWidth - cch;
        if (ptft->fLeft)
            cchRight = cchPad;
        else
            cchLeft = cchPad;
    }
    WritePad(postrm, ch, cchLeft);
    postrm->CbWrite(pchz, cch);
    WritePad(postrm, ' ', cchRight);
}
