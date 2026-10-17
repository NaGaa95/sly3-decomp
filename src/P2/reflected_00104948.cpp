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
void func_001703C8(void *receiver, int, int);
CRef func_00104948(void *p, int c, void *aref);
}
CRef func_00104948(void *p, int c, void *aref)
{
    int ak[2] = {0x2002, 0x1064};
    int value0;
    int value1;
    CRef ref = func_0024B2B8(2, aref, ak, &value0, &value1);
    ref.Decref();
    ref.InitTag(0x22);
    func_001703C8(*(void **)((char *)p + 0x10D0), value0, value1);
    return ref;
}
