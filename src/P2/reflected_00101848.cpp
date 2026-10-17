// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
typedef int qword __attribute__((mode(TI)));
struct CRef {
    short m_tagk; short m_word2; union { int n; float g; void *pv; } u;
    CRef() { m_tagk = -1; }
    CRef(const CRef &r);
    void Decref();
    void InitTag(int tagk);
    ~CRef() { Decref(); }
};
extern "C" {
CRef func_0024B2B8(int c, void *aref, int *ak, ...);
void func_0014B6E8(void *receiver, int, int, float, float, int);
CRef func_00101848(void *p, int c, void *aref);
}
CRef func_00101848(void *p, int c, void *aref)
{
    int ak[5] = {0x2088, 0x6, 0x1, 0x1, 0x100D};
    int value0;
    int value1;
    float value2;
    float value3;
    int value4;
    CRef ref = func_0024B2B8(5, aref, ak, &value0, &value1, &value2, &value3, &value4);
    ref.Decref();
    ref.InitTag(0x22);
    func_0014B6E8(p, value0, value1, value2, value3, value4);
    return ref;
}
