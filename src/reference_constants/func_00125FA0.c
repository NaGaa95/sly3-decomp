// Reference algorithm: src/hand/func_00120CC8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct CRef { int m_tagk; int m_tag; } CRef;
void func_00125E98(CRef *ret, void *pbasic, int cref, CRef *aref, int k);
CRef *func_00125FA0(CRef *ret, void *pbasic, int cref, CRef *aref)
{
    func_00125E98(ret, pbasic, cref, aref, 0x72);
    return ret;
}
