// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
typedef struct CRef { int m_tagk; int m_tag; } CRef;
void Decref__4CRef(CRef *pref);
CRef *__4CRefRC4CRef(CRef *pref, CRef *prefSrc);
void InitTag__4CRef(CRef *pref, int tagk);
void *func_002459F8(int n);
void func_00244F08(void *p, int n);
void func_0012B218(CRef *pref, void *p);
CRef *func_001270F8(CRef *ret, void *pbasic, CRef *aref)
{
    int n = aref[1].m_tag;
    void *p = func_002459F8(aref[0].m_tag);
    func_00244F08(p, n);
    func_0012B218(ret, p);
    return ret;
}
