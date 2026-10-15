// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct SAAF { char pad[0xC]; float dtLoopMin; float dtLoopMax; };
struct SHUFFLE { char pad[0x50]; float dtPauseMin; float dtPauseMax; };
void InitSaa(SHUFFLE *p, SAAF *psaaf);
extern "C" void func_00237760(SHUFFLE *pshuffle, SAAF *psaaf)
{
    float dtMax, dtMin;
    InitSaa(pshuffle, psaaf);
    dtMin = psaaf->dtLoopMin;
    dtMax = psaaf->dtLoopMax;
    pshuffle->dtPauseMax = dtMax;
    pshuffle->dtPauseMin = dtMin;
}
