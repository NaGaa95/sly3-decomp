// Reference algorithm: src/hand/func_00127190.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct CRef { short m_tagk; short unknown_tag_padding; union { int n; float g; void *pv; } u; } CRef;
typedef struct LO { char pad[0xC]; struct LO *pnext; } LO;
typedef struct BASIC { char pad[0x18]; LO *plo; } BASIC;
void func_0012BC20(CRef *pref);
CRef *func_0012AF00(CRef *pref, CRef *prefSrc);
CRef *func_0012B3B0(CRef *pref, CRef *prefSrc);
CRef *func_001296F0(CRef *ret, LO *plo, CRef *aref);
CRef *func_001290B0(CRef *ret, BASIC *pbasic, CRef *aref)
{
    CRef ref;
    CRef refT;
    LO *plo;
    ref.m_tagk = -1;
    plo = pbasic->plo;
    do {
        func_001296F0(&refT, plo, aref);
        func_0012B3B0(&ref, &refT);
        func_0012BC20(&refT);
        plo = plo->pnext;
    } while (plo);
    func_0012AF00(ret, &ref);
    func_0012BC20(&ref);
    return ret;
}
