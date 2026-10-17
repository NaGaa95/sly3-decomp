// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
typedef int qword __attribute__((mode(TI)));
struct CRef {
    int m_tagk; union { int n; float g; void *pv; } u;
    CRef() { m_tagk = -1; }
    CRef(const CRef &r);
    void Decref();
    void InitTag(int tagk);
    ~CRef() { Decref(); }
};
extern "C" {
CRef func_0024B2B8(int c, void *aref, int *ak, ...);
void func_0015C650(void *receiver, int, int);
CRef func_001066B8(void *p, int c, void *aref);
}
CRef func_001066B8(void *p, int c, void *aref)
{
    int ak[2] = {0x6, 0x1047};
    int value0;
    int value1;
    CRef ref = func_0024B2B8(2, aref, ak, &value0, &value1);
    ref.Decref();
    ref.InitTag(0x22);
    func_0015C650((char *)p + 0x120, value0, value1);
    return ref;
}
