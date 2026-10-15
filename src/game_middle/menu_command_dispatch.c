// SLY3_CFLAGS: -Os -G0
struct MenuCommandView {
    unsigned char opaque00[0x50];
    int mode;
};
struct PMF { short delta, pad; int (*pfn)(void *); };
struct S { int x0, x4; struct PMF pmf; int x10; };
typedef char MethodSizeIsEight[(sizeof(struct PMF) == 8) ? 1 : -1];
typedef char WorkerSizeIsTwenty[(sizeof(struct S) == 20) ? 1 : -1];
extern struct S D_00388BF0;
extern const struct PMF D_00323D18, D_00323BE8, D_00323D20;
void func_001CEEC0(struct S *worker, struct PMF method);
void func_001D0C08(void *menu, int mode);
void func_001D1648(void);

void func_001D1370(void *menu)
{
    struct MenuCommandView *context = menu;
    switch (context->mode) {
    case 0x28:
        func_001D1648();
        break;
    case 0x1D:
        func_001CEEC0(&D_00388BF0, D_00323D18);
        func_001D0C08(menu, 0x1E);
        break;
    case 0x20:
        func_001CEEC0(&D_00388BF0, D_00323BE8);
        func_001D0C08(menu, 0x21);
        break;
    case 0x2D:
        func_001CEEC0(&D_00388BF0, D_00323D20);
        func_001D0C08(menu, 0x2E);
        break;
    case 0x1B:
        func_001D0C08(menu, 0x3F);
        break;
    case 0x24:
        func_001D0C08(menu, 0x3E);
        break;
    }
}
