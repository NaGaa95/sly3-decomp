// Sly 2 reference: src/hand/func_0014BC78.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
extern char D_003175E0[];
extern char D_003175E8[];
extern int D_0036BB40;
extern int D_0036BB44;
int func_002A0E38(unsigned int lsn, unsigned int c, void *buf, void *mode);
int func_241E88(int n);
int func_002A0480(int n);
int func_002A10D8(void);
void func_001630B0(unsigned int lsn, unsigned int c, void *buf, int fMode)
{
    void *mode;
    if (fMode == 1) mode = D_003175E0;
    else mode = D_003175E8;
    do {
        D_0036BB40 = func_002A0E38(lsn, c, buf, mode);
        if (D_0036BB40 == 1) break;
        func_002A0480(0);
        D_0036BB44 = func_002A10D8();
    } while (1);
}
