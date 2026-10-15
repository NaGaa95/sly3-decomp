// Reference algorithm: src/hand/func_001244E8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct CRef { short m_tagk; short unknown_tag_padding; int m_tag; } CRef;
typedef struct LO { char pad[4]; struct LO *pc; char pad2[0x30]; void *pv; } LO;
typedef struct G { char pad[0x4634]; void *pv; } G;
extern G D_00475480;
void *func_0017E1D8(G *pg, int k, int a, LO *b, void *c);
void func_0012B768(CRef *pref, void *p);
CRef *func_0012AF00(CRef *pref, CRef *prefSrc);
void func_0012BC20(CRef *pref);
CRef *func_00126470(CRef *ret, void *pbasic, CRef *aref)
{
    CRef ref;
    LO *b;
    LO *plo;
    void *pv;
    ref.m_tagk = -1;
    b = (LO *)aref[1].m_tag;
    if (aref[2].m_tagk) {
        plo = ((LO *)aref[2].m_tag)->pc;
    } else {
        plo = b;
    }
    {
        G *pg = &D_00475480;
        int a = aref[0].m_tag;
        func_0012B768(&ref, func_0017E1D8(pg, 4, a, b, plo ? plo->pv : pg->pv));
    }
    func_0012AF00(ret, &ref);
    func_0012BC20(&ref);
    return ret;
}
