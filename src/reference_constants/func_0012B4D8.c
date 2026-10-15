// Reference algorithm: src/hand/func_00129780.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct MATRIX4 { float m[4][4]; } __attribute__((aligned(16))) MATRIX4;
typedef struct CRef { short m_tagk; short unknown_tag_padding; void *m_p; } CRef;
typedef struct MR { MATRIX4 mat; int cref; } MR;
extern char D_004D2F40[];
MR *func_0011E118(void *pslotheap);
void func_0012BC20(CRef *pref);
CRef *func_0012B4D8(CRef *pref, MATRIX4 *pmat)
{
    MR *p;
    func_0012BC20(pref);
    pref->m_tagk = 0x19;
    p = func_0011E118(D_004D2F40);
    p->cref = 0;
    pref->m_p = p;
    p->cref++;
    ((MR *)pref->m_p)->mat = *pmat;
    return pref;
}
