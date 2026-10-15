// Reference algorithm: src/hand/func_00126438.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct CRef { short m_tagk; short unknown_tag_padding; int m_tag; } CRef;
void func_0012BC20(CRef *pref);
CRef *func_0012AF00(CRef *pref, CRef *prefSrc);
int func_00129B18(void *a, void *b, int c, CRef *d);
typedef struct BASIC { int pad[1]; void *p; } BASIC;
CRef *func_001283D0(CRef *ret, BASIC *pbasic, void *aref)
{
    CRef ref;
    ref.m_tagk = -1;
    func_00129B18(aref, pbasic->p, 1, &ref);
    func_0012AF00(ret, &ref);
    func_0012BC20(&ref);
    return ret;
}
