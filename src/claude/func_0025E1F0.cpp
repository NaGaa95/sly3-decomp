// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Read a float script variable of slot i (0 when nothing is loaded).
struct CRef;
extern "C" void func_0012BC20(CRef *pr);
struct CRef {
    short tag;
    short cref;
    float g;
    CRef(const CRef &r);
    ~CRef() { func_0012BC20(this); }
};
struct G { void *p; char pad[0x330 - 4]; void *a[1]; };
extern G D_004793C8;
extern "C" CRef func_002BC010(void *pv, int k);
extern "C" float func_0025E1F0(int i, int k)
{
    if (D_004793C8.p) {
        CRef r = func_002BC010(D_004793C8.a[i], k);
        return r.g;
    }
    return 0.0f;
}
