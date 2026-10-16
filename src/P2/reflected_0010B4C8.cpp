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
struct MaskFlagsView { char prefix[0x18]; int flags; };
struct MaskTableView { char prefix[0x134]; MaskFlagsView *flags; };
struct MaskReceiverView { char prefix[0x20]; MaskTableView *table; };
extern "C" {
CRef func_0024B2B8(int c, void *aref, int *ak, ...);
CRef func_0010B4C8(void *p, int c, void *aref);
}
CRef func_0010B4C8(void *p, int c, void *aref)
{
    int ak[1] = {0x5};
    int mask;
    CRef ref = func_0024B2B8(1, aref, ak, &mask);
    ref = (((MaskReceiverView *)p)->table->flags->flags & mask) != 0;
    return ref;
}
