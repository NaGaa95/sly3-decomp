// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0
// Same original collector/pool/block-registration algorithm as the maintained2BB7F0 factory.
typedef struct RuntimePoolFreeList {
    unsigned char opaque00[0x0c];
    void *available;
} RuntimePoolFreeList;
typedef struct RuntimeFactoryCell002BAAB8 {
    unsigned char opaque00[8];
    void *first;
    unsigned char opaque0c[8];
    void *second;
    void *third;
} RuntimeFactoryCell002BAAB8;
typedef char RuntimeFactoryPhysicalCell[(sizeof(RuntimeFactoryCell002BAAB8) == 28) ? 1 : -1];
extern unsigned char D_004D2D60[];
extern unsigned char D_004D2CE0[];
extern int D_0036AE44;
extern int D_004793C4;
extern char D_0036B138[];
void func_0012A3D0(void *collector);
void *func_0011E118(void *pool);
void *func_002B4658(void *cell);

void *func_002BAAB8(void)
{
    RuntimeFactoryCell002BAAB8 *cell;
    if (((RuntimePoolFreeList *)D_004D2D60)->available == 0) {
        if (D_004793C4 == 0)
            func_0012A3D0(D_0036B138);
        if (((RuntimePoolFreeList *)D_004D2D60)->available == 0)
            ((void **)D_004D2CE0)[D_0036AE44++] = func_0011E118(D_004D2D60);
    }
    cell = func_0011E118(D_004D2D60);
    func_002B4658(cell);
    cell->first = 0;
    cell->second = 0;
    cell->third = 0;
    return cell;
}
