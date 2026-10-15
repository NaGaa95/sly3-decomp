// Reference algorithm: src/hand/func_00123608.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct Range { float low, high; };
typedef struct CRef {
    short m_tagk;
    short unknown_tag_padding;
    union { int n; float g; const struct Range *range; } u;
} CRef;
void func_0012BC20(CRef *pref);
void func_0012BAE8(CRef *pref, CRef *prefSrc);
int func_0011EE30(const struct Range *range, float g);
CRef *func_00125328(CRef *ret, void *pbasic, CRef *aref)
{
    const struct Range *range = aref[0].u.range;
    CRef ref;
    int f;
    func_0012BAE8(&ref, &aref[1]);
    f = func_0011EE30(range, ref.u.g) != 0;
    ret->m_tagk = 0x15;
    ret->u.n = f;
    func_0012BC20(&ref);
    return ret;
}
