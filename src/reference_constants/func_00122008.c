// Reference algorithm: src/hand/func_00120398.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct CRef { short m_tagk; short unknown_tag_padding; union { int n; float g; } u; } CRef;
CRef *func_00122008(CRef *ret, CRef *aref, int op)
{
    float ag[2];
    int i;
    int f;
    for (i = 0; i < 2; i++) {
        if (aref[i].m_tagk == 0x14)
            ag[i] = aref[i].u.g;
        else
            ag[i] = (float)aref[i].u.n;
    }
    switch (op) {
    case 0:
        f = ag[0] < ag[1];
        break;
    case 1:
        f = ag[0] <= ag[1];
        break;
    case 2:
        f = ag[0] > ag[1];
        break;
    case 3:
        f = ag[0] >= ag[1];
        break;
    }
    ret->u.n = f;
    ret->m_tagk = 0x15;
    return ret;
}
