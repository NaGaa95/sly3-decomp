typedef struct CRef { short tagk; short pad; void *pv; } CRef;
void func_0012BDD8(CRef *pref, int tagk);
void func_0012B1D8(CRef *pref, void *pnode);
CRef *func_00122838(CRef *pref, void *pframe, void **pargs)
{
    void *pnode = ((void **)pargs[1])[3];
    if (pnode == 0) {
        func_0012BDD8(pref, 0);
    } else {
        func_0012B1D8(pref, pnode);
    }
    return pref;
}
