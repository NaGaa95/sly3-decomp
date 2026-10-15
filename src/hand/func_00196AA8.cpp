// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
enum ZPK { ZPK_Nil = -1 };
struct LO;
struct ZPR { ZPK zpk; ZPK zpk2; LO *ploSource; char pad[0x630 - 12]; };
extern "C" void func_00292034(void *p, int c, int n);
extern "C" void func_00196AA8(ZPR *pzpr, ZPK zpk, LO *ploSource) { func_00292034(pzpr, 0, sizeof(ZPR)); pzpr->zpk = pzpr->zpk2 = zpk; pzpr->ploSource = ploSource; }
