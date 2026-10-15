// Reference algorithm: src/hand/func_001256E0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct CRef { short m_tagk; short unknown_tag_padding; int m_tag; } CRef;
void func_0012BC20(CRef *pref);
CRef *func_0012AF00(CRef *pref, CRef *prefSrc);
void func_0012B2F0(CRef *pref, int f);
int func_0021F410(int n);
CRef *func_00127600(CRef *ret, void *pbasic, CRef *aref)
{
    CRef ref;
    ref.m_tagk = -1;
    func_0012B2F0(&ref, func_0021F410(aref->m_tag) != 0);
    func_0012AF00(ret, &ref);
    func_0012BC20(&ref);
    return ret;
}
