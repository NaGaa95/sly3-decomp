// Reference algorithm: src/hand/func_001258F0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct CRef { short m_tagk; short unknown_tag_padding; int m_tag; } CRef;
void func_0012BC20(CRef *pref);
CRef *func_0012AF00(CRef *pref, CRef *prefSrc);
CRef *func_00127988(CRef *ret)
{
    CRef ref;
    ref.m_tagk = -1;
    func_0012AF00(ret, &ref);
    func_0012BC20(&ref);
    return ret;
}
