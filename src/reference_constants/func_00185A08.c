// Reference algorithm: src/hand/func_00162050.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct CRef { int m_tagk; int m_tag; } CRef;
void func_0024B330(CRef *pref, void *p, int n, int c, int *pc, int *ai);
int func_001859A8(int c, int *ai);
void func_0012BC20(CRef *pref);
int func_00185A08(void *p)
{
    int ai[8];
    CRef ref;
    int c;
    int grf;
    func_0024B330(&ref, p, 0x1047, 6, &c, ai);
    grf = func_001859A8(c, ai);
    func_0012BC20(&ref);
    return grf;
}
