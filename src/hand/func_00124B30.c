// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
typedef struct CRef { int m_tagk; int m_tag; } CRef;
void Decref__4CRef(CRef *pref);
CRef *__4CRefRC4CRef(CRef *pref, CRef *prefSrc);
void InitTag__4CRef(CRef *pref, int tagk);
typedef struct MATRIX4 { float m[4][4]; } __attribute__((aligned(16))) MATRIX4;
void func_0011D628(MATRIX4 *pmat, int n);
void func_0012B008(CRef *pref, MATRIX4 *pmat);
CRef *func_00124B30(CRef *ret, void *pbasic, CRef *aref)
{
    CRef ref;
    MATRIX4 mat;
    func_0011D628(&mat, aref->m_tag);
    func_0012B008(&ref, &mat);
    __4CRefRC4CRef(ret, &ref);
    Decref__4CRef(&ref);
    return ret;
}
