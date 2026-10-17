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
void func_00255B28(void *receiver, void *, void *);
CRef func_00104498(void *p, int c, void *aref);
}
CRef func_00104498(void *p, int c, void *aref)
{
    int ak[2] = {0xA002, 0xA002};
    CRef value0;
    CRef value1;
    CRef ref = func_0024B2B8(2, aref, ak, &value0, &value1);
    ref.Decref();
    ref.InitTag(0x22);
    func_00255B28(p, &value0, &value1);
    return ref;
}
