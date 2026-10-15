// Reference algorithm: src/hand/func_00123380.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct CRef { short m_tagk; short unknown_tag_padding; union { int n; float g; void *p; } u; } CRef;
void func_0012BC20(CRef *pref);
void func_0012BAE8(CRef *pref, CRef *prefSrc);
CRef *func_001250A0(CRef *ret, void *pbasic, CRef *aref)
{
    float *a = (float *)aref[0].u.p;
    CRef ref;
    float t, g;
    func_0012BAE8(&ref, &aref[1]);
    t = ref.u.g;
    g = a[0] + t * (a[1] + t * a[2]);
    ret->m_tagk = 0x14;
    ret->u.g = g;
    func_0012BC20(&ref);
    return ret;
}
