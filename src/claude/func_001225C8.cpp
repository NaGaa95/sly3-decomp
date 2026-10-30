// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct CRef {
    short m_tagk; short m_pad; int m_tag;
    CRef(int n, int tagk) { m_tag = n; m_tagk = tagk; }
};
extern "C" CRef func_001225C8(void *pbasic, CRef *aref);
CRef func_001225C8(void *pbasic, CRef *aref)
{
    int f = 0;
    if (aref->m_tagk == 0x1D || aref->m_tagk == 0) {
        f = 1;
    }
    return CRef(f, 0x15);
}
