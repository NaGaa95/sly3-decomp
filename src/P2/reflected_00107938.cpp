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
void func_001FDD40(void *receiver, int, int, int, int, int, int, int, int);
CRef func_00107938(void *p, int c, void *aref);
}
CRef func_00107938(void *p, int c, void *aref)
{
    int ak[8] = {0x5, 0x5, 0x5, 0x5, 0x5, 0x5, 0x5, 0x5};
    int value0;
    int value1;
    int value2;
    int value3;
    int value4;
    int value5;
    int value6;
    int value7;
    CRef ref = func_0024B2B8(8, aref, ak, &value0, &value1, &value2, &value3, &value4, &value5, &value6, &value7);
    ref.Decref();
    ref.InitTag(0x22);
    func_001FDD40(p, value0, value1, value2, value3, value4, value5, value6, value7);
    return ref;
}
