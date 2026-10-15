// Reference algorithm: src/hand/func_00129878.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct CLQ { int a, b; } CLQ;
typedef struct CRef { short m_tagk; short unknown_tag_padding; void *m_p; } CRef;
typedef struct LR { CLQ v; int cref; } LR;
extern char D_004D2F70[];
LR *func_0011E118(void *pslotheap);
void func_0012BC20(CRef *pref);
CRef *func_0012B5D0(CRef *pref, CLQ *pv)
{
    LR *p;
    func_0012BC20(pref);
    pref->m_tagk = 0x1B;
    p = func_0011E118(D_004D2F70);
    p->cref = 0;
    pref->m_p = p;
    p->cref++;
    ((LR *)pref->m_p)->v = *pv;
    return pref;
}
