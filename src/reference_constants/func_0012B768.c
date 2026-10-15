// Reference algorithm: src/hand/func_00129A10.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct CRef { short m_tagk; short unknown_tag_padding; void *m_p; } CRef;
typedef struct VT { short d; short pad; void (*fn)(void *); } VT;
typedef struct O { int pad[3]; VT *vt; } O;
void func_0012BC20(CRef *pref);
CRef *func_0012B768(CRef *pref, O *p)
{
    if (p)
        p->vt[1].fn((char *)p + p->vt[1].d);
    func_0012BC20(pref);
    pref->m_p = p;
    pref->m_tagk = 0x1F;
    return pref;
}
