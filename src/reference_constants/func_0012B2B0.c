// Reference algorithm: src/hand/func_00129558.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct CRef { short m_tagk; short unknown_tag_padding; float m_g; } CRef;
void func_0012BC20(CRef *pref);
CRef *func_0012B2B0(CRef *pref, float g)
{
    func_0012BC20(pref);
    pref->m_g = g;
    pref->m_tagk = 0x14;
    return pref;
}
