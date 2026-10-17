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
void func_00257E98(void *receiver, qword, qword, qword, void *);
CRef func_00104C90(void *p, int c, void *aref);
}
CRef func_00104C90(void *p, int c, void *aref)
{
    int ak[4] = {0x2, 0x2, 0x2, 0xA};
    union { qword q; } value0;
    union { qword q; } value1;
    union { qword q; } value2;
    union { qword q; } value3;
    CRef ref = func_0024B2B8(4, aref, ak, &value0, &value1, &value2, &value3);
    ref.Decref();
    ref.InitTag(0x22);
    func_00257E98(p, value0.q, value1.q, value2.q, &value3);
    return ref;
}
