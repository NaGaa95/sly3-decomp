// Reference algorithm: src/hand/func_001220B8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct CRef { int m_tagk; union { int n; float g; void *pv; } u; } CRef;
void func_0012BC20(CRef *pref);
void func_0012BDD8(CRef *pref, int tagk);
void func_0012BAE8(CRef *pref, CRef *prefSrc);
CRef *func_0012AF00(CRef *pref, CRef *prefSrc);
CRef *func_00123E48(CRef *ret, void *pbasic, CRef *aref)
{
    CRef ref;
    int i;
    float *pg;
    func_0012BDD8(&ref, 0x1A);
    pg = (float *)ref.u.pv;
    for (i = 0; i < 3; i++) {
        CRef tmp;
        func_0012BAE8(&tmp, &aref[i]);
        pg[i] = tmp.u.g;
        func_0012BC20(&tmp);
    }
    func_0012AF00(ret, &ref);
    func_0012BC20(&ref);
    return ret;
}
