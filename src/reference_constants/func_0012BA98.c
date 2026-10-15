// Reference algorithm: src/hand/func_00129D58.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct CRef { short m_tagk; short unknown_tag_padding; union { int n; float g; } u; } CRef;
CRef *func_0012AF00(CRef *pref, CRef *prefSrc);
CRef *func_0012BA98(CRef *pref, CRef *prefSrc)
{
    if (prefSrc->m_tagk == 0x13) {
        func_0012AF00(pref, prefSrc);
    } else {
        float g = prefSrc->u.g;
        pref->m_tagk = 0x13;
        pref->u.n = (int)g;
    }
    return pref;
}
