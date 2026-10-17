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
struct VirtualEntry { short delta, pad; int (*call)(void *, int); };
struct VirtualReceiver { char prefix[0xC]; VirtualEntry *vtable; };
extern "C" {
CRef func_0024B2B8(int c, void *aref, int *ak, ...);
CRef func_0010A598(void *p, int c, void *aref);
}
CRef func_0010A598(void *p, int c, void *aref)
{
    int ak[1] = {0x1011};
    int value0;
    CRef ref = func_0024B2B8(1, aref, ak, &value0);
    VirtualEntry *entry = &((VirtualReceiver *)p)->vtable[80];
    ref = entry->call((char *)p + entry->delta, value0) != 0;
    return ref;
}
