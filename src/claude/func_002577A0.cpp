// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct CRef;
extern "C" {
void func_0012BDD8(CRef *pr, int tagk);
CRef *func_0012B3B0(CRef *pd, const CRef *ps);
void func_0012BC20(CRef *pr);
void *memset(void *, int, unsigned int);
}
struct CRef {
    short tag;
    short cref;
    int val;
    CRef() { tag = -1; }
    CRef(const CRef &r);
    CRef &operator=(const CRef &r) { func_0012B3B0(this, &r); return *this; }
    ~CRef() { func_0012BC20(this); }
};
struct L;
extern "C" CRef func_0024B330(L *list, int tag, int unused, int *count, int *dest);
extern "C" int func_002577A0(L *list, float *out);
int func_002577A0(L *list, float *out)
{
    CRef r;
    int a[2];
    int count;
    int sum;
    unsigned i, j;
    memset(a, 0, sizeof(a));
    r = func_0024B330(list, 5, 2, &count, a);
    sum = 0;
    for (i = 0; i < 2; i++)
        sum += a[i];
    if (sum == 0) {
        out[0] = 1.0f;
        for (i = 1; i < 2; i++)
            out[i] = 0.0f;
    } else {
        for (j = 0; j < 2; j++)
            out[j] = (float)a[j] / (float)sum;
    }
    return 1;
}
