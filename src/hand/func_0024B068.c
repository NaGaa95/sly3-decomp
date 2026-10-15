// Assign the explicit typed output array from the original references, converting integer and float tags as needed and copying vector/matrix records through the complete output-type dispatch table.
// Reference algorithm: src/hand/func_00201110.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
typedef struct CRef { short tagk; short reserved; union { int n; float g; void *pv; } u; } CRef;
typedef struct CREFA { CRef r; } __attribute__((aligned(16))) CREFA;
typedef struct { qword a[3]; } M3;
typedef struct { int a, b; } V2;
typedef struct { int a, b, c; } V3;
CRef *func_0012BDD8(CRef *pref, int tagk);
void func_0012B3B0(CRef *pref, CRef *prefSrc);
void func_0012BC20(CRef *pref);
CRef *func_0012BA98(CRef *ret, CRef *pref);
CRef *func_0012BAE8(CRef *ret, CRef *pref);

CRef *func_0024B068(CRef *ret, int c, CRef *aref, int *aotype, void **apv)
{
    CREFA ref;
    CREFA t;
    int i;
    ref.r.tagk = -1;
    for (i = 0; i < c; i++) {
        int ot;
        void *pv;
        func_0012B3B0(&ref.r, &aref[i]);
        ot = aotype[i];
        pv = apv[i];
        switch (ot) {
        case 5: case 6: case 7: case 8:
        case 0xE: case 0xF: case 0x10: case 0x11:
        case 0x13: case 0x14: case 0x15: case 0x17:
            if (ref.r.tagk == 0x13) {
                *(int *)pv = ref.r.u.n;
            } else {
                CREFA tmp;
                CRef *pt = &t.r;
                pt->tagk = -1;
                func_0012BA98(&tmp.r, &ref.r);
                func_0012B3B0(pt, &tmp.r);
                func_0012BC20(&tmp.r);
                *(int *)pv = t.r.u.n;
                func_0012BC20(pt);
            }
            break;
        case 1:
            if (ref.r.tagk == 0x14) {
                *(float *)pv = ref.r.u.g;
            } else {
                CREFA tmp;
                CRef *pt = &t.r;
                pt->tagk = -1;
                func_0012BAE8(&tmp.r, &ref.r);
                func_0012B3B0(pt, &tmp.r);
                func_0012BC20(&tmp.r);
                *(float *)pv = t.r.u.g;
                func_0012BC20(pt);
            }
            break;
        case 4:
            *(M3 *)pv = *(M3 *)ref.r.u.pv;
            break;
        case 2:
        case 9:
            *(qword *)pv = *(qword *)ref.r.u.pv;
            break;
        case 0xA:
            *(V2 *)pv = *(V2 *)ref.r.u.pv;
            break;
        case 0xB:
            *(V3 *)pv = *(V3 *)ref.r.u.pv;
            break;
        default:
            if (ot & 0x8000)
                func_0012B3B0((CRef *)pv, &ref.r);
            else if (ot & 0x1000)
                goto store;
            else if (ot & 0x2000)
        case 0:
            store:
                *(int *)pv = ref.r.u.n;
            break;
        case 0xD:
        case 0x16:
            break;
        }
    }
    func_0012BDD8(ret, 0x22);
    func_0012BC20(&ref.r);
    return ret;
}
