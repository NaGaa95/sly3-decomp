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
void func_0014DAE0(void *receiver, int, int, int);
CRef func_0010D008(void *p, int c, void *aref);
}
CRef func_0010D008(void *p, int c, void *aref)
{
    int ak[3] = {0x6, 0x103C, 0x6};
    int value0;
    int value1;
    int value2;
    CRef ref = func_0024B2B8(3, aref, ak, &value0, &value1, &value2);
    ref.Decref();
    ref.InitTag(0x22);
    func_0014DAE0(p, value0, value1, value2);
    return ref;
}
