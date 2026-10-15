// Reference algorithm: src/hand/func_001235A8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct LM { float low, high; };
typedef struct CRef {
    short m_tagk;
    short unknown_tag_padding;
    union { int n; float g; struct LM *range; } u;
} CRef;
void func_0012BC20(CRef *pref);
void func_0012BAE8(CRef *pref, CRef *prefSrc);
float func_0011EE68(struct LM *range, float g);
CRef *func_001252C8(CRef *ret, void *pbasic, CRef *aref)
{
    struct LM *range = aref[0].u.range;
    CRef ref;
    float g;
    func_0012BAE8(&ref, &aref[1]);
    g = func_0011EE68(range, ref.u.g);
    ret->u.g = g;
    ret->m_tagk = 0x14;
    func_0012BC20(&ref);
    return ret;
}
