// Reference algorithm: src/hand/func_00124640.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct CRef { short m_tagk; short reserved; int m_tag; } CRef;
void func_0012BC20(CRef *pref);
CRef *func_0012AF00(CRef *pref, CRef *prefSrc);
void func_0012B768(CRef *pref, void *p);
extern void *D_00468D24;
CRef *func_001266B8(CRef *ret)
{
    CRef ref;
    ref.m_tagk = -1;
    func_0012B768(&ref, D_00468D24);
    func_0012AF00(ret, &ref);
    func_0012BC20(&ref);
    return ret;
}
