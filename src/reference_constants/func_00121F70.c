// Reference algorithm: src/hand/func_00120CC8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct CRef { short m_tagk; short unknown_tag_padding; int m_tag; } CRef;
void func_0012BDD8(CRef *ret, int k);
CRef *func_00121F70(CRef *ret)
{
    func_0012BDD8(ret, 0x22);
    return ret;
}
