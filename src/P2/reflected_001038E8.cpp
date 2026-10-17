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
void func_002535F0(void *receiver, void *, int, int, int, int);
CRef func_001038E8(void *p, int c, void *aref);
}
CRef func_001038E8(void *p, int c, void *aref)
{
    int ak[5] = {0x900F, 0x6, 0x6, 0x6, 0x6};
    CRef value0;
    int value1;
    int value2;
    int value3;
    int value4;
    CRef ref = func_0024B2B8(5, aref, ak, &value0, &value1, &value2, &value3, &value4);
    ref.Decref();
    ref.InitTag(0x22);
    func_002535F0(p, &value0, value1, value2, value3, value4);
    return ref;
}
