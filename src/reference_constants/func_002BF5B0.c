// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0
// Original fixed-pool allocation and block registration; no original storage owned.
// The0036B138 argument is a mutable collector receiver, not a message string.
typedef struct RuntimePoolFreeList {
    unsigned char opaque00[0x0c];
    void *available;
} RuntimePoolFreeList;
typedef struct RuntimeHalfCellView {
    unsigned char opaque00[8];
    short state;
} RuntimeHalfCellView;
extern unsigned char D_004D2F10[];
extern unsigned char D_004D2E90[];
extern int D_0036AE6C;
extern int D_004793C4;
extern char D_0036B138[];
extern void func_0012A3D0(void *collector);
extern void *func_0011E118(void *pool);
extern void *func_002B4DD8(void *cell);

void *func_002BF5B0(void)
{
    RuntimeHalfCellView *cell;
    if (((RuntimePoolFreeList *)D_004D2F10)->available == 0) {
        if (D_004793C4 == 0)
            func_0012A3D0(D_0036B138);
        if (((RuntimePoolFreeList *)D_004D2F10)->available == 0)
            ((void **)D_004D2E90)[D_0036AE6C++] = func_0011E118(D_004D2F10);
    }
    cell = func_0011E118(D_004D2F10);
    func_002B4DD8(cell);
    cell->state = -1;
    return cell;
}
