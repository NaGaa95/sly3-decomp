// SLY3_CFLAGS: -Os -G0
extern int D_0034A26C;
extern int D_0034A278;
extern int D_004C8D80[];
extern int func_002A0480(void);
extern int func_002908F0(void);
extern void func_00293CF8(void *begin, void *end);
int func_00291A10(int mode)
{
    int ready;
    unsigned char *end;
    if (D_0034A26C == 0)
        return func_002A0480();
    end = (unsigned char *)D_004C8D80 + 63;
    func_00293CF8(D_004C8D80, end);
    ready = D_004C8D80[0] == 0;
    D_0034A278 = ready;
    if (ready == 1) return 0;
    if (mode == 1) return 1;
    while (ready == 0) {
        func_002908F0();
        func_00293CF8(D_004C8D80, end);
        ready = D_004C8D80[0] == 0;
        D_0034A278 = ready;
    }
    return 0;
}
