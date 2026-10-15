// Reference algorithm: src/hand/func_001250D8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
typedef struct CRef { int m_tagk; int m_tag; } CRef;
typedef struct MATRIX4 { qword a[4]; } MATRIX4;
void func_0012BDD8(CRef *pref, int tagk);
void func_001C9708(MATRIX4 *pmat, int a, int b, int c);
CRef *func_0012AF00(CRef *pref, CRef *prefSrc);
void func_0012BC20(CRef *pref);
CRef *func_00126FD8(CRef *ret, void *pbasic, CRef *aref)
{
    CRef ref;
    MATRIX4 mat;
    MATRIX4 *pmat;
    func_0012BDD8(&ref, 0x19);
    pmat = (MATRIX4 *)ref.m_tag;
    func_001C9708(&mat, aref[0].m_tag, aref[1].m_tag, aref[2].m_tag);
    *pmat = mat;
    func_0012AF00(ret, &ref);
    func_0012BC20(&ref);
    return ret;
}
