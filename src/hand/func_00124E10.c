// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
typedef int TI __attribute__((mode(TI)));
typedef struct MATRIX3 { float mat[3][4]; } __attribute__((aligned(16))) MATRIX3;
typedef union CRefPayload { int word; const MATRIX3 *matrix; } CRefPayload;
typedef struct CRef { int m_tagk; CRefPayload m_tag; } CRef;
void Decref__4CRef(CRef *pref);
CRef *__4CRefRC4CRef(CRef *pref, CRef *prefSrc);
void func_0012AFA0(CRef *pref, TI vec);
TI func_0011D3C0(const MATRIX3 *matrix);
CRef *func_00124E10(CRef *ret, void *pbasic, CRef *aref)
{
    CRef ref;
    func_0012AFA0(&ref, func_0011D3C0(aref->m_tag.matrix));
    __4CRefRC4CRef(ret, &ref);
    Decref__4CRef(&ref);
    return ret;
}
