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
void func_00154D10(void *receiver, float, float, void *, float, float, qword, qword);
CRef func_001097D0(void *p, int c, void *aref);
}
CRef func_001097D0(void *p, int c, void *aref)
{
    int ak[7] = {0x1, 0x1, 0xA, 0x1, 0x1, 0x2, 0x2};
    float value0;
    float value1;
    union { qword q; } value2;
    float value3;
    float value4;
    union { qword q; } value5;
    union { qword q; } value6;
    CRef ref = func_0024B2B8(7, aref, ak, &value0, &value1, &value2, &value3, &value4, &value5, &value6);
    ref.Decref();
    ref.InitTag(0x22);
    func_00154D10(p, value0, value1, &value2, value3, value4, value5.q, value6.q);
    return ref;
}
