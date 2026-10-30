// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sly 2 reference: /home/claude/decomp src/hand/SwitchTex0__8CFontBrxP4GIFS.cpp (same body).
struct GIFS {
    void AddPrimPack(int a, int b, unsigned long c);
    void PackAD(long a, long b);
    void AddPrimList(int a, unsigned long b);
};
class CFontBrx {
public:
    char pad[0x50];
    unsigned long m_tex0;
    int FUN_15F148(GIFS *pgifs);
    void SwitchTex0(GIFS *pgifs);
};
void CFontBrx::SwitchTex0(GIFS *pgifs)
{
    int f = FUN_15F148(pgifs);
    pgifs->AddPrimPack(6, 1, 0xe);
    if (f)
        pgifs->PackAD(0x3f, 0);
    pgifs->PackAD(6, m_tex0);
    pgifs->PackAD(0, 0x1d6);
    pgifs->AddPrimList(5, 0x43431);
}
