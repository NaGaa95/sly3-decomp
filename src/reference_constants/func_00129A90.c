// Reference algorithm: src/hand/func_00127CF0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct CRef { short m_tagk; short unknown_tag_padding; int m_tag; } CRef;
void func_0012BC20(CRef *pref);
CRef *func_0012AF00(CRef *pref, CRef *prefSrc);
void func_0012BDD8(CRef *pref, int tagk);
void func_0012B3B0(CRef *pref, CRef *prefSrc);
CRef *func_00129B58(void *a, void *b, int c);
CRef *func_00129A90(CRef *ret, void *a, void *b, CRef *pref)
{
    CRef ref;
    CRef *p;
    ref.m_tagk = -1;
    p = func_00129B58(a, b, 1);
    if (p)
        func_0012B3B0(p, pref);
    func_0012BC20(&ref);
    func_0012BDD8(&ref, 0x22);
    func_0012AF00(ret, &ref);
    func_0012BC20(&ref);
    return ret;
}
