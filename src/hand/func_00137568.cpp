// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct ASEG; struct ALO; struct ASEGA; enum SEEK { SEEK_0 };
void EnsureAseg(ASEG *, ALO *, SEEK, float, float, int, ASEGA **);
extern "C" ASEGA *func_00137568(ASEG *paseg, ALO *paloRoot, SEEK seek, float t, float svt, int grfapl)
{ ASEGA *pasega; EnsureAseg(paseg, paloRoot, seek, t, svt, grfapl, &pasega); return pasega; }
