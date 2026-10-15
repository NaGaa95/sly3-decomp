// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0
// Same original collector/pool/block-registration algorithm as the maintained2BB7F0 factory.
typedef struct RuntimePoolFreeList {
    unsigned char opaque00[0x0c];
    void *available;
} RuntimePoolFreeList;
typedef struct RuntimeFactoryCell002BAE00 {
    unsigned char opaque00[12];
    short state;
    unsigned char opaque0e[6];
    void *value;
} RuntimeFactoryCell002BAE00;
typedef char RuntimeFactoryPhysicalCell[(sizeof(RuntimeFactoryCell002BAE00) == 24) ? 1 : -1];
extern unsigned char D_004D2BB0[];
extern unsigned char D_004D2B30[];
extern int D_0036AE1C;
extern int D_004793C4;
extern char D_0036B138[];
void func_0012A3D0(void *collector);
void *func_0011E118(void *pool);
void *func_002B3ED8(void *cell);

void *func_002BAE00(void)
{
    RuntimeFactoryCell002BAE00 *cell;
    if (((RuntimePoolFreeList *)D_004D2BB0)->available == 0) {
        if (D_004793C4 == 0)
            func_0012A3D0(D_0036B138);
        if (((RuntimePoolFreeList *)D_004D2BB0)->available == 0)
            ((void **)D_004D2B30)[D_0036AE1C++] = func_0011E118(D_004D2BB0);
    }
    cell = func_0011E118(D_004D2BB0);
    func_002B3ED8(cell);
    cell->state = -1;
    cell->value = 0;
    return cell;
}
