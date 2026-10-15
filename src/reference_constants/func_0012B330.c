// Reference algorithm: src/hand/func_00129518.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct CRef { short m_tagk; short unknown_tag_padding; int m_tag; } CRef;
void func_0012BC20(CRef *pref);
CRef *func_0012B330(CRef *pref, int n)
{
    func_0012BC20(pref);
    pref->m_tag = n;
    pref->m_tagk = 0x16;
    return pref;
}
