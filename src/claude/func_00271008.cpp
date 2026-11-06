// SLY3_CFLAGS: -Os -G0 -fno-exceptions
// Adapted from Sly 2 CchOstrmPrintf__FP5OSTRMPcT1 (Sly 3 tests the format string at the loop top).
struct OSTRM { char pad[0x10]; int cchWritten; };
struct TFT {int fLeft,fPlus,fSpace,fPrefix,fZero,fPrec0,width,precision,cbits,matrixRows,vectorColumns;unsigned char conversion;int fUpper;};
extern "C" char *func_002716C8(char *p, int ch);
extern "C" int func_002715F8(char *p);
extern "C" int func_0025A2D0(OSTRM *postrm, char *pb, int cb);
extern "C" int func_0026FC50(char *pchz, TFT *ptft, char **ppv);
extern "C" void func_00270C70(TFT *ptft, OSTRM *postrm, char **ppv, char *pchz, int cch);
extern "C" int func_00271008(OSTRM *postrm, char *pchzFormat, char *pv)
{
    TFT tft;
top:
    if (*(unsigned char *)pchzFormat) {
        register char *pchz __asm__("$16") = func_002716C8(pchzFormat, '%'); /* pin: pchz in s0 */
        int cch = pchz - pchzFormat;
        do {
            if (!pchz) {
                cch = func_002715F8(pchzFormat);
                pchz = pchzFormat + cch;
            }
        } while (0);
        while (cch != 0) {
            if (func_0025A2D0(postrm, pchzFormat, cch) < cch)
                goto done;
            pchzFormat = pchz;
            break;
        }
        if (*(unsigned char *)pchzFormat == '%') {
            int cchFmt = func_0026FC50(pchzFormat, &tft, &pv);
            func_00270C70(&tft, postrm, &pv, pchzFormat, cchFmt);
            pchzFormat += cchFmt;
        }
        goto top;
    }
done:
    return postrm->cchWritten;
}
