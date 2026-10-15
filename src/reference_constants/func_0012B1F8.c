// Reference algorithm: src/hand/func_00129480.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct CRef { short m_tagk; short unknown_tag_padding; int m_tag; } CRef;
CRef *func_0012B1F8(CRef *ret, int *p)
{
    ret->m_tag = (int)p;
    ret->m_tagk = 0x1E;
    (*p)++;
    return ret;
}
