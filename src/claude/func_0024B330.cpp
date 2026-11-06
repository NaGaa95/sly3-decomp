// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Cf. Sly 2 src/hand/func_002013D8.cpp (Sly 3 CRef: short tag, tag values 2 lower).
struct CRef;
extern "C" {
void func_0012BDD8(CRef *pr, int tagk);
CRef *func_0012B3B0(CRef *pd, const CRef *ps);
void func_0012BC20(CRef *pr);
}
struct CRef {
    short tag;
    short cref;
    int val;
    CRef() { tag = -1; }
    CRef(int k) { func_0012BDD8(this, k); }
    CRef &operator=(const CRef &r) { func_0012B3B0(this, &r); return *this; }
    ~CRef() { func_0012BC20(this); }
};
struct E { CRef ref; int pad; E *next; };
struct L { short count; short pad; E *first; };
extern "C" CRef func_0024B2B8(int count, CRef *values, int *tags, ...);
extern "C" CRef func_0024B330(L *list, int tag, int unused, int *count, int *dest)
{
    if (list->count == 0) {
        *count = 0;
        return CRef(0x22);
    }
    *count = 0;
    for (E *e = list->first; e; e = e->next) {
        CRef r;
        r = func_0024B2B8(1, &e->ref, &tag, &dest[*count]);
        ++*count;
    }
    return CRef(0x22);
}
