// Reference algorithm: src/hand/func_001236F8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct CRef { short m_tagk; short unknown_tag_padding; int m_tag; } CRef;
void func_0012B270(CRef *pref, int n);
void func_0012B2B0(CRef *pref, float g);
CRef *func_0012AF00(CRef *pref, CRef *prefSrc);
void func_0012BC20(CRef *pref);
CRef *func_00125650(CRef *ret, void *pbasic, CRef *aref)
{
    CRef ref;
    ref.m_tagk = -1;
    if (aref->m_tagk == 0x13) {
        int n = aref->m_tag;
        func_0012B270(&ref, n < 0 ? -n : n);
    } else {
        float g = *(float *)&aref->m_tag;
        if (g < 0.0f) g = -g;
        func_0012B2B0(&ref, g);
    }
    func_0012AF00(ret, &ref);
    func_0012BC20(&ref);
    return ret;
}
