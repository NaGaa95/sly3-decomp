// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct WR; struct WRE;
enum ENSK { ENSK_0 };
enum WREK { WREK_Circle = 0, WREK_Bend = 1 };
WRE *PwreGetWrCur(WR *pwr, ENSK ensk, WREK wrek);
extern "C" WRE *func_0028A620(WR *pwr, ENSK ensk)
{
    return PwreGetWrCur(pwr, ensk, WREK_Bend);
}
