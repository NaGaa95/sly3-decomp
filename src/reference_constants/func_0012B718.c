// Reference algorithm: src/hand/func_00129970.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct CRef { short m_tagk; short unknown_tag_padding; int m_tag; } CRef;
void func_0012BC20(CRef *pref);
CRef *func_0012B718(CRef *pref, int *p)
{
    (*p)++;
    func_0012BC20(pref);
    pref->m_tag = (int)p;
    pref->m_tagk = 0x1E;
    return pref;
}
