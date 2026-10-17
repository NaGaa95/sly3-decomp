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
void func_00179E58(void *receiver, int, int, qword, qword, float, float);
CRef func_00107CC0(void *p, int c, void *aref);
}
CRef func_00107CC0(void *p, int c, void *aref)
{
    int ak[6] = {0x1028, 0x2002, 0x2, 0x2, 0x1, 0x1};
    int value0;
    int value1;
    union { qword q; } value2;
    union { qword q; } value3;
    float value4;
    float value5;
    CRef ref = func_0024B2B8(6, aref, ak, &value0, &value1, &value2, &value3, &value4, &value5);
    ref.Decref();
    ref.InitTag(0x22);
    func_00179E58(p, value0, value1, value2.q, value3.q, value4, value5);
    return ref;
}
