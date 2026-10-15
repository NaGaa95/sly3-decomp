// Sly 2 reference: src/hand/func_00161798.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
typedef struct CRef { short m_tagk; short reserved; int m_tag; } CRef;
extern int D_00479504;
extern char D_00468D30[];
void func_002BC010(CRef *pref, int a, void *b);
void func_0012BC20(CRef *pref);
int func_001852E0(void *context)
{
    CRef ref;
    int n;
    func_002BC010(&ref, D_00479504, D_00468D30);
    n = ref.m_tag;
    func_0012BC20(&ref);
    return n;
}
