// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0
// Original fixed-pool allocation and block registration; no original storage owned.
// The0036B138 argument is a mutable collector receiver, not a message string.
typedef struct RuntimePoolFreeList {
    unsigned char opaque00[0x0c];
    void *available;
} RuntimePoolFreeList;
typedef struct RuntimeWordCellView {
    unsigned char opaque00[8];
    int state;
} RuntimeWordCellView;
extern unsigned char D_004D2E38[];
extern unsigned char D_004D2DB8[];
extern int D_0036AE58;
extern int D_004793C4;
extern char D_0036B138[];
extern void func_0012A3D0(void *collector);
extern void *func_0011E118(void *pool);
extern void *func_002B4A18(void *cell);

void *func_002BB7F0(void)
{
    RuntimeWordCellView *cell;
    if (((RuntimePoolFreeList *)D_004D2E38)->available == 0) {
        if (D_004793C4 == 0)
            func_0012A3D0(D_0036B138);
        if (((RuntimePoolFreeList *)D_004D2E38)->available == 0)
            ((void **)D_004D2DB8)[D_0036AE58++] = func_0011E118(D_004D2E38);
    }
    cell = func_0011E118(D_004D2E38);
    func_002B4A18(cell);
    cell->state = 0;
    return cell;
}
