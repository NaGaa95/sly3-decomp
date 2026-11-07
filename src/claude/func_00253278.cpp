// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// SLY3_ASFIX: engine-local-jumps
// Score of mask b against a: 0 unless a is a subset of b, else the number of set bits of a&b (A53 draft, by-value BITS params).
struct BITS { unsigned char b[16]; };
static inline BITS operator&(const BITS &a, const BITS &b)
{
    BITS r;
    for (int i = 0; i < 16; i++)
        r.b[i] = a.b[i] & b.b[i];
    return r;
}
static inline int operator!=(const BITS &a, const BITS &b)
{
    for (int i = 0; i < 16; i++)
        if (a.b[i] != b.b[i])
            return 1;
    return 0;
}
static inline int Count(const BITS &a)
{
    int c = 0;
    for (int i = 0; i < 128; i++) {
        int m = 1 << (i & 7);
        if (a.b[i / 8] & m)
            c++;
    }
    return c;
}
extern "C" int func_00253278(BITS a, BITS b)
{
    BITS r = a & b;
    if (r != a)
        return 0;
    return Count(r);
}
