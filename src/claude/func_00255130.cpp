// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Pick the entry whose mask scores best against the first mask bit set in `mask` (BITS byte-loop operators, func_00252AD0 ctor).
struct BITS {
    unsigned char ab[16];
    BITS() {}
    BITS(int n) asm("func_00252AD0");
    BITS operator&(const BITS &other) const
    {
        BITS r;
        for (int j = 0; j < 16; j++) r.ab[j] = ab[j] & other.ab[j];
        return r;
    }
    int operator!=(const BITS &other) const
    {
        for (int j = 0; j < 16; j++)
            if (ab[j] != other.ab[j]) return 1;
        return 0;
    }
    int operator==(const BITS &other) const
    {
        for (int j = 0; j < 16; j++)
            if (ab[j] != other.ab[j]) return 0;
        return 1;
    }
};
struct ENT { int n; char pad[0xC]; BITS bits; };
struct P { char pad[0x4D0]; int c; char pad4D4[0xC]; ENT ae[1]; };
struct BEST { ENT *pe; int n; };
extern "C" {
extern BITS D_00475440;
int func_00253278(BITS a, BITS b);
ENT *func_00255130(P *p, BITS mask);
}
ENT *func_00255130(P *p, BITS mask)
{
    BITS acc = D_00475440;
    ENT *pe;
    int n;
    int i;
    pe = 0;
    n = 0;
    for (i = 0; i < 70; i++) {
        acc = BITS(i);
        if ((mask & acc) != D_00475440) break;
    }
    for (int k = 0; k < p->c; k++) {
        ENT *e = &p->ae[k];
        int v = func_00253278(e->bits, mask);
        if (!v) continue;
        if ((e->bits & acc) == D_00475440) continue;
        if (e->n != -1 && n < v) {
            n = v;
            pe = e;
        }
    }
    return pe;
}
