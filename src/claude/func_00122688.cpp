// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct CRef {
    short m_tagk; short m_pad; int m_tag;
    CRef(int n, int tagk) { m_tag = n; m_tagk = tagk; }
};
extern "C" CRef func_00122688(void *pbasic, CRef *aref);
CRef func_00122688(void *pbasic, CRef *aref)
{
    int f = 0;
    if (aref->m_tagk == 0x1E || aref->m_tagk == 0x17) {
        f = 1;
    }
    return CRef(f, 0x15);
}
