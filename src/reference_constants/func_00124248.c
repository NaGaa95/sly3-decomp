// Reference algorithm: src/hand/func_001224A8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct CRef { short m_tagk; short unknown_tag_padding; int m_tag; } CRef;
typedef float (*PFNG)(float);
extern PFNG D_00342010[];
void func_0012B2B0(CRef *pref, float g);
CRef *func_0012AF00(CRef *pref, CRef *prefSrc);
void func_0012BC20(CRef *pref);
CRef *func_00124248(CRef *ret, CRef *parg, int i)
{
    CRef ref;
    float g;
    ref.m_tagk = -1;
    if (parg->m_tagk == 0x14) {
        g = *(float *)&parg->m_tag;
    } else {
        g = (float)parg->m_tag;
    }
    func_0012B2B0(&ref, D_00342010[i](g));
    func_0012AF00(ret, &ref);
    func_0012BC20(&ref);
    return ret;
}
