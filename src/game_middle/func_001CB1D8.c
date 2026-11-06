// SLY3_CFLAGS: -Os -G0 -ffast-math
// Frame loop entry of the game (same routine as Sly 2 func_001A7518): store the two start arguments, run the one-time
// setup, then update/draw the scene objects every frame forever (never returns).
extern int D_00370CC0, D_00370CC4;
extern void *D_0036B330;
extern int D_0036C650;
extern char D_00475480[], D_0046F540[], D_0036BB98[], D_0036BC10[];
void func_0029A458(void);
void func_001CB620(void);
void func_00184918(void);
void func_00168FE0(void *p);
void func_0025C2A8(void *p);
void func_00165430(void *p, int n);
void func_001A77A0(void);
void func_00162E80(void);
void func_0027D7E8(void *p);
void func_0021D9E0(void *p);
void func_00182C68(void);
int func_0015A5D8(void *p);
void func_00209C40(void *p);
void func_00175268(void *p);
void func_0021DBE8(void *p);
void func_0015A600(void *p);
void func_00182EE0(void);
void func_001CB1D8(int a, int b)
{
    func_0029A458();
    D_00370CC0 = a;
    D_00370CC4 = b;
    func_001CB620();
    func_00184918();
    func_00168FE0(D_0036BC10);
    for (;;) {
        func_0025C2A8(D_00475480);
        func_00165430(D_0036BB98, 0);
        func_001A77A0();
        func_00162E80();
        func_0027D7E8(D_00475480);
        func_0021D9E0(D_0046F540);
        func_00182C68();
        if (!D_0036B330 || func_0015A5D8(D_0036B330)) {
            func_00209C40(D_00475480);
            func_00175268(D_00475480);
            func_0021DBE8(D_0046F540);
        }
        if (D_0036B330)
            func_0015A600(D_0036B330);
        func_00182EE0();
        D_0036C650++;
    }
}
