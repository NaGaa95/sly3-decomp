// Reference algorithm: src/hand/func_00125060.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int TI __attribute__((mode(TI)));
typedef struct CRef { int m_tagk; void *m_p; } CRef;
void func_0012BC20(CRef *pref);
CRef *func_0012AF00(CRef *pref, CRef *prefSrc);
void func_0012BDD8(CRef *pref, int tagk);
TI func_001C94E8(void *a, void *b, TI v);
CRef *func_00126F68(CRef *ret, void *pbasic, CRef *aref)
{
    CRef ref;
    TI *pv;
    func_0012BDD8(&ref, 0x18);
    pv = ref.m_p;
    *pv = func_001C94E8(aref[0].m_p, aref[1].m_p, *(TI *)aref[2].m_p);
    func_0012AF00(ret, &ref);
    func_0012BC20(&ref);
    return ret;
}
