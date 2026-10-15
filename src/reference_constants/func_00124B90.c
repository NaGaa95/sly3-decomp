// Reference algorithm: src/hand/func_00125738.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct CRef { short m_tagk; short unknown_tag_padding; int m_tag; } CRef;
void func_0012BC20(CRef *pref);
CRef *func_0012AF00(CRef *pref, CRef *prefSrc);
void func_0012BDD8(CRef *pref, int tagk);
void func_0011D740(int a, int b);
CRef *func_00124B90(CRef *ret, void *pbasic, CRef *aref)
{
    CRef ref;
    func_0012BDD8(&ref, 0x19);
    func_0011D740(aref[0].m_tag, ref.m_tag);
    func_0012AF00(ret, &ref);
    func_0012BC20(&ref);
    return ret;
}
