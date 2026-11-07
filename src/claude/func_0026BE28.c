// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_0026BE28: actor init: base init, angle limits and tuning defaults, flag bit 2 on its (tagged) flags word.
struct S
{
    char pad0[0x3C];
    unsigned int grf3C;
    char pad40[0x190 - 0x40];
    int n190;
    char pad194[0x1B4 - 0x194];
    float g1B4;
    char pad1B8[0x1E4 - 0x1B8];
    float g1E4, g1E8, g1EC, g1F0;
    char pad1F4[0x1FC - 0x1F4];
    float g1FC, g200, g204, g208, g20C, g210, g214, g218, g21C;
    char pad220[4];
    float g224;
    char pad228[4];
    float g22C, g230;
};
void func_001F3B50(struct S *p);
void func_001F43F8(struct S *p, int n);
void func_00240E58(struct S *p, int grf, int n);

static inline int FPtr(unsigned int grf) { return !(grf & 1); }
void func_0026BE28(struct S *p)
{
    unsigned int grf;
    func_001F3B50(p);
    p->g1E4 = -1.5707964f;
    p->g1E8 = 1.5707964f;
    p->g1EC = -1.17f;
    p->g1F0 = -1.04f;
    func_001F43F8(p, 0x28);
    func_00240E58(p, 0x3FFFFFF, 2);
    grf = p->grf3C;
    p->n190 = -1;
    p->g224 = 100.0f;
    p->g230 = 1.0f;
    p->g21C = 100.0f;
    p->g22C = 3.0f;
    p->g1FC = 1.17f;
    p->g204 = 1.04f;
    p->g200 = 2.0f;
    p->g208 = 1.3f;
    p->g20C = 1.0f;
    p->g210 = 1.0f;
    p->g214 = 0.5f;
    p->g218 = 0.5f;
    p->g1B4 = 2.0f;
    if (FPtr(grf))
        *(unsigned int *)grf |= 2;
    else
        p->grf3C = grf | 2;
}
