// Reference algorithm: src/hand/func_0013E690.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct CRef { short m_tagk; short unknown_tag_padding; union { int n; float g; } u; } CRef;
int func_00118FF8(void *pbs);
int func_001191E0(void *pbs);
float func_00119260(void *pbs);
int func_00119178(void *pbs);
int func_001190A8(void *pbs);
void func_0012B088(CRef *ret, float *ag);
void func_0012B0F0(CRef *ret, float *ag);
void func_0012AF38(CRef *ret, float *ag);
void func_0012BDD8(CRef *ret, int tagk);
CRef *func_00150960(CRef *ret, int k, void *pbs)
{
    float ag[3];
    switch (k) {
    case 0:
        {
            int f = func_00118FF8(pbs) != 0;
            ret->m_tagk = 0x15;
            ret->u.n = f;
        }
        break;
    case 5: case 6:
        ret->u.n = func_001191E0(pbs);
        ret->m_tagk = 0x13;
        break;
    case 1:
        ret->u.g = func_00119260(pbs);
        ret->m_tagk = 0x14;
        break;
    case 7: case 14: case 15: case 16: case 17: case 19: case 20: case 21: case 23:
        ret->u.n = func_00119178(pbs);
        ret->m_tagk = 0x13;
        break;
    case 9:
        {
            float *pg = ag;
            int j;
            for (j = 0; j < 3; j++)
                *pg++ = func_00119260(pbs);
        }
        func_0012B088(ret, ag);
        break;
    case 10:
        ag[0] = func_00119260(pbs);
        ag[1] = func_00119260(pbs);
        func_0012B0F0(ret, ag);
        break;
    case 2:
        {
            float *pg = ag;
            int j;
            for (j = 0; j < 3; j++)
                *pg++ = func_00119260(pbs);
        }
        func_0012AF38(ret, ag);
        break;
    default:
        if (((k & ~0x8000) >> 12) == 1) {
            ret->u.n = func_001190A8(pbs);
            ret->m_tagk = 0x13;
        } else {
            func_0012BDD8(ret, 0x22);
        }
        break;
    }
    return ret;
}
