// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Mask gate called from func_00255FE0: filters by actor kind/mode and BITS masks (byte-loop operators as in
// func_00255130); &m is kept in a pointer local so it lives in an s-reg across the calls.
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
struct L14 { void *p0; };
struct L1E8 { char pad[0x14]; L14 *p14; };
struct A { char pad[0x1E8]; L1E8 *p1E8; };
struct ENT { char pad[8]; int n8; char padC[4]; float f10; };
struct P { char pad[0x2F0]; int mode; BITS grf; char pad304[0x3DC - 0x304]; int n3DC; char pad3E0[0x10D0 - 0x3E0]; void *p10D0; };
extern "C" {
extern BITS D_00475440;
extern struct CLOCK { float t; float dt; } g_clock;
int func_0013B500(void *, int);
ENT *func_00170528(void *, void *);
int func_00255D78(P *p, A *other, const BITS *mask);
}
int func_00255D78(P *p, A *other, const BITS *mask)
{
    BITS m = *mask;
    BITS *pm = &m;
    if (p->n3DC) return 0;
    if (func_0013B500(other, 0x59)) other = (A *)other->p1E8->p14->p0;
    if (func_0013B500(other, 0x35) && p->mode != 1 && p->mode != 2 && (p->grf & BITS(6)) == D_00475440) return 1;
    ENT *e = func_00170528(p->p10D0, other);
    if (!e || !e->n8 || g_clock.t - e->f10 < 0.2f || (p->grf & *pm) != D_00475440) return 1;
    return 0;
}
