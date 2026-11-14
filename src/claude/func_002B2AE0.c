// Sly 2 counterpart: _pictureCodingExtension (decomp src/lib/_pictureCodingExtension.c)
// Matches only with the empty asm barriers after each 'd->x = call()' statement: emulates Sony's scheduler keeping
// the return-value consumer right after the call (gcc3 in_post_call_group_p-like). Without them 24/121 differ (sw moves into jal slot).
// SLY3_CC: tools/third_party/ee-gcc2.95.3-114
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
// SLY3_SAVES: sd
typedef struct {
    char p0[0xE8]; int xE8;
    char pEC[0x174 - 0xEC]; int f_code[4]; int picture_structure; int top_field_first;
    int frame_pred_frame_dct; int concealment_motion_vectors; int repeat_first_field; int progressive_frame;
} D;
unsigned int func_002B0B78(D *d, int n);
#define IPU_CTRL (*(volatile unsigned int *)0x10002010)
void func_002B2AE0(D *d)
{
    unsigned int ps;

    d->f_code[0] = func_002B0B78(d, 4);
    __asm__ volatile("");
    d->f_code[1] = func_002B0B78(d, 4);
    __asm__ volatile("");
    d->f_code[2] = func_002B0B78(d, 4);
    __asm__ volatile("");
    d->f_code[3] = func_002B0B78(d, 4);
    __asm__ volatile("");
    IPU_CTRL = (IPU_CTRL & 0xFFFCFFFF) | (func_002B0B78(d, 2) << 16);
    ps = func_002B0B78(d, 2);
    d->picture_structure = ps;
    if (d->xE8 == 0)
        d->xE8 = ps;
    d->top_field_first = func_002B0B78(d, 1);
    __asm__ volatile("");
    d->frame_pred_frame_dct = func_002B0B78(d, 1);
    __asm__ volatile("");
    d->concealment_motion_vectors = func_002B0B78(d, 1);
    __asm__ volatile("");
    IPU_CTRL = (IPU_CTRL & 0xFFBFFFFF) | (func_002B0B78(d, 1) << 22);
    IPU_CTRL = (IPU_CTRL & 0xFFDFFFFF) | (func_002B0B78(d, 1) << 21);
    IPU_CTRL = (IPU_CTRL & 0xFFEFFFFF) | (func_002B0B78(d, 1) << 20);
    d->repeat_first_field = func_002B0B78(d, 1);
    __asm__ volatile("");
    func_002B0B78(d, 1);
    d->progressive_frame = func_002B0B78(d, 1);
    __asm__ volatile("");
    if (func_002B0B78(d, 1)) {
        func_002B0B78(d, 1);
        func_002B0B78(d, 3);
        func_002B0B78(d, 1);
        func_002B0B78(d, 7);
        func_002B0B78(d, 8);
    }
}
