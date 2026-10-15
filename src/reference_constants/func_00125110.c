// Reference algorithm: src/hand/func_001233F0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct CRef { short m_tagk; short unknown_tag_padding; union { int n; float g; void *pv; } u; } CRef;
typedef struct LM { float gMin; float gMax; } LM;
void func_0012BC20(CRef *pref);
void func_0012BAE8(CRef *pref, CRef *prefSrc);
static __inline__ float GLimit(float g, float gMin, float gMax)
{
    if (g < gMin)
        return gMin;
    if (gMax < g)
        return gMax;
    return g;
}
CRef *func_00125110(CRef *ret, void *pbasic, CRef *aref)
{
    float *c = (float *)aref[0].u.pv;
    LM *plm = (LM *)aref[1].u.pv;
    CRef ref;
    float g;
    func_0012BAE8(&ref, &aref[2]);
    g = ref.u.g;
    ret->u.g = GLimit(c[0] + g * (c[1] + g * c[2]), plm->gMin, plm->gMax);
    ret->m_tagk = 0x14;
    func_0012BC20(&ref);
    return ret;
}
