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
    CRef &operator=(const CRef &r);
    CRef &operator=(void *pv);
    CRef &operator=(bool f);
};
struct QueryTableView { char prefix[0x134]; void *object; };
struct QueryReceiverView { char prefix[0x20]; QueryTableView *table; };
extern "C" {
CRef func_0024B2B8(int c, void *aref, int *ak, ...);
int func_001A7A80(void *object, int n, float g);
CRef func_0010B400(void *p, int c, void *aref);
}
CRef func_0010B400(void *p, int c, void *aref)
{
    int ak[2] = {0x5, 0x1};
    int value0;
    float value1;
    CRef ref = func_0024B2B8(2, aref, ak, &value0, &value1);
    ref = (float)func_001A7A80(((QueryReceiverView *)p)->table->object, value0, value1) != 0;
    return ref;
}
