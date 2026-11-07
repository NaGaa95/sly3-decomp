// Sly 2 counterpart: _getAllRefs (decomp src/lib/_getAllRefs.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct {
    char p0[0x130]; int second_field;
    char p134[0x160 - 0x134]; int picture_coding_type;
    char p164[0x184 - 0x164]; int picture_structure;
    char p188[0x1C8 - 0x188]; void *fwd; void *bwd;
    char p1D0[0x1D8 - 0x1D0]; void *fwd_top; void *bwd_top;
    char p1E0[0x1E8 - 0x1E0]; void *fwd_bot; void *bwd_bot;
    char p1F0[0x820 - 0x1F0]; int x820;
} D;
void func_002AEFE0(D *d, void *ref, int sfield, int dfield, int oy, int h, int x, int y, int dx, int dy, int fld, int avg);
void func_002AE500(D *d, int DMV[][2], int *dmvector, int mvx, int mvy);
void func_002AE4B8(D *d, const char *fmt, ...);

void func_002AE688(D *d, int bx, int by, int mbtype, int mtype, int *pmv, int *mvfs, int *dmvector)
{
    int DMV[2][2];
    void *ref[2][2];
    int stw = 0;
    int cur, sel = 1;

    *(int *)((char *)d + d->x820 * 0x140 + 0x6CC) = 0;
    if ((mbtype & 8) || d->picture_coding_type == 2) {
        if (d->picture_structure == 3) {
            if (mtype == 2 || !(mbtype & 8)) {
                func_002AEFE0(d, d->fwd, 0, 0, 0, 16, bx, by, pmv[0], pmv[1], 0, stw);
            } else if (mtype == sel) {
                func_002AEFE0(d, d->fwd, mvfs[0], 0, 0, 8, bx, by, pmv[0], pmv[1] >> 1, 1, stw);
                func_002AEFE0(d, d->fwd, mvfs[2], 1, 0, 8, bx, by, pmv[4], pmv[5] >> 1, 1, stw);
            } else if (mtype == 3) {
                func_002AE500(d, DMV, dmvector, pmv[0], pmv[1] >> 1);
                func_002AEFE0(d, d->fwd, 0, 0, 0, 8, bx, by, pmv[0], pmv[1] >> 1, sel, 0);
                func_002AEFE0(d, d->fwd, 1, 0, 0, 8, bx, by, DMV[0][0], DMV[0][1], sel, sel);
                func_002AEFE0(d, d->fwd, 1, 1, 0, 8, bx, by, pmv[0], pmv[1] >> 1, sel, 0);
                func_002AEFE0(d, d->fwd, 0, 1, 0, 8, bx, by, DMV[1][0], DMV[1][1], sel, sel);
            } else {
                func_002AE4B8(d, "(a) invalid motion_type(%d)-0", mtype);
            }
        } else {
            int two = 2;
            cur = d->picture_structure == two;
            ref[0][0] = d->fwd_top;
            ref[0][1] = d->fwd_bot;
            ref[1][0] = d->bwd_top;
            ref[1][1] = d->bwd_bot;
            sel = 0;
            if (d->picture_coding_type == two && d->second_field)
                sel = cur != mvfs[0];
            if (mtype == 1 || !(mbtype & 8)) {
                func_002AEFE0(d, ref[sel][mvfs[0]], 0, 0, 0, 16, bx, by, pmv[0], pmv[1], 0, stw);
            } else if (mtype == 2) {
                func_002AEFE0(d, ref[sel][mvfs[0]], 0, 0, 0, 8, bx, by, pmv[0], pmv[1], 0, stw);
                sel = 0;
                if (d->picture_coding_type == 2 && d->second_field) {
                    if (cur != mvfs[2])
                        sel = 1;
                    else
                        sel = 0;
                }
                func_002AEFE0(d, ref[sel][mvfs[2]], 0, 0, 8, 8, bx, by, pmv[4], pmv[5], 0, stw);
            } else if (mtype == 3) {
                if (d->second_field)
                    sel = 1;
                else
                    sel = 0;
                func_002AE500(d, DMV, dmvector, pmv[0], pmv[1]);
                func_002AEFE0(d, ref[0][cur], 0, 0, 0, 16, bx, by, pmv[0], pmv[1], 0, 0);
                func_002AEFE0(d, ref[sel][!cur], 0, 0, 0, 16, bx, by, DMV[0][0], DMV[0][1], 0, 1);
            } else {
                func_002AE4B8(d, "(b) invalid motion_type(%d)-1", mtype);
            }
        }
        stw = 1;
    }
    if (mbtype & 4) {
        if (d->picture_structure == 3) {
            sel = 1;
            if (mtype == 2) {
                func_002AEFE0(d, d->bwd, 0, 0, 0, 16, bx, by, pmv[2], pmv[3], 0, stw);
            } else {
                func_002AEFE0(d, d->bwd, mvfs[1], 0, 0, 8, bx, by, pmv[2], pmv[3] >> 1, sel, stw);
                func_002AEFE0(d, d->bwd, mvfs[3], 1, 0, 8, bx, by, pmv[6], pmv[7] >> 1, sel, stw);
            }
        } else if (mtype == 1) {
            func_002AEFE0(d, mvfs[1] ? d->bwd_bot : d->bwd_top, 0, 0, 0, 16, bx, by, pmv[2], pmv[3], 0, stw);
        } else if (mtype == 2) {
            func_002AEFE0(d, mvfs[1] ? d->bwd_bot : d->bwd_top, 0, 0, 0, 8, bx, by, pmv[2], pmv[3], 0, stw);
            func_002AEFE0(d, mvfs[3] ? d->bwd_bot : d->bwd_top, 0, 0, 8, 8, bx, by, pmv[6], pmv[7], 0, stw);
        } else {
            func_002AE4B8(d, "(c) invalid motion_type(%d)-2", mtype);
        }
    }
}
