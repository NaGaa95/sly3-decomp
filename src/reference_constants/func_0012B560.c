// Reference algorithm: src/hand/func_001296A8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int TI __attribute__((mode(TI)));
typedef struct CRef { short m_tagk; short unknown_tag_padding; void *m_p; } CRef;
typedef struct VR { TI vec; int cref; } VR;
extern char D_004D2F58[];
VR *func_0011E118(void *pslotheap);
void func_0012BC20(CRef *pref);
CRef *func_0012B560(CRef *pref, TI *pvec)
{
    VR *p;
    func_0012BC20(pref);
    pref->m_tagk = 0x1A;
    p = func_0011E118(D_004D2F58);
    p->cref = 0;
    pref->m_p = p;
    p->cref++;
    ((VR *)pref->m_p)->vec = *pvec;
    return pref;
}
