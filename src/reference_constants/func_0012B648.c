// Reference algorithm: src/hand/func_001298F0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct CLT { int a, b, c; } CLT;
typedef struct CRef { short m_tagk; short unknown_tag_padding; void *m_p; } CRef;
typedef struct TR { CLT v; int cref; } TR;
extern char D_004D2F88[];
TR *func_0011E118(void *pslotheap);
void func_0012BC20(CRef *pref);
CRef *func_0012B648(CRef *pref, CLT *pv)
{
    TR *p;
    func_0012BC20(pref);
    pref->m_tagk = 0x1C;
    p = func_0011E118(D_004D2F88);
    p->cref = 0;
    pref->m_p = p;
    p->cref++;
    ((TR *)pref->m_p)->v = *pv;
    return pref;
}
