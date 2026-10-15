// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0
// Same original collector/pool/block-registration algorithm as the maintained2BB7F0 factory.
typedef struct RuntimePoolFreeList {
    unsigned char opaque00[0x0c];
    void *available;
} RuntimePoolFreeList;
typedef struct RuntimeFactoryCell002BA6B8 {
    unsigned char opaque00[12];
    void *value;
} RuntimeFactoryCell002BA6B8;
typedef char RuntimeFactoryPhysicalCell[(sizeof(RuntimeFactoryCell002BA6B8) == 16) ? 1 : -1];
extern unsigned char D_004D2AD8[];
extern unsigned char D_004D2A58[];
extern int D_0036AE08;
extern int D_004793C4;
extern char D_0036B138[];
void func_0012A3D0(void *collector);
void *func_0011E118(void *pool);
void *func_002B3B18(void *cell);

void *func_002BA6B8(void)
{
    RuntimeFactoryCell002BA6B8 *cell;
    if (((RuntimePoolFreeList *)D_004D2AD8)->available == 0) {
        if (D_004793C4 == 0)
            func_0012A3D0(D_0036B138);
        if (((RuntimePoolFreeList *)D_004D2AD8)->available == 0)
            ((void **)D_004D2A58)[D_0036AE08++] = func_0011E118(D_004D2AD8);
    }
    cell = func_0011E118(D_004D2AD8);
    func_002B3B18(cell);
    cell->value = 0;
    return cell;
}
