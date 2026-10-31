// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_001830F8: the main frame loop (double-buffered frame records, render passes, present).
struct FR { int x0; int x4; char pad8[0x24 - 0x8]; int x24; char pad28[0x30 - 0x28]; int grf; char pad34[0x190 - 0x34]; };
struct WORLD { char pad[0x3EB8]; int cso; void *apso[1]; };
extern int D_0036C684, D_0036C678, D_0036C688;
extern volatile int D_0036C68C;
extern struct FR *D_0036C680;
extern struct FR D_0036C330[];
extern int D_0036DC98, D_0036DCA8;
extern int D_00467B00;
extern int D_0036DBEC;
extern struct { int x0; int x4; int x8; int xC; } D_0036DBE0;
extern char D_0036E3D0[], D_0036E470[], D_0036E500[], D_0036E5A0[];
extern struct WORLD D_00475480;
extern int D_0036BD3C, D_0036BD40;
void func_002936E0(int sema);
void func_002936C0(int sema);
void func_00238060(void);
int func_00182FB8(void);
void func_00196050(int n, int k);
void CopyAqw__FPvT0i(void *dst, void *src, int c);
void func_00293920(int n);
void func_00195760(int a, int b);
void func_00167DD8(void *pso, struct FR *pfr);
void func_001837E0(void);
void sceDmaSync(int ch, int mode, int timeout);
void func_00195688(void);
void func_001956B8(void);
void func_00183038(int n);
void func_001830F8(void)
{
    for (;;) {
        int n;
        D_0036C68C = 1;
        func_002936E0(D_0036C684);
        D_0036C68C = 0;
        {
            register struct FR *base __asm__("$3") = D_0036C330; /* register pin: frame array base in v1 like the target */
            D_0036C680 = &base[D_0036C678];
        }
        if ((unsigned int)++D_0036C678 >= 2)
            D_0036C678 = 0;
        do { /* do{}while(0) block (macro-like): its loop notes give the .p2align at the copy-if join and the bne target-thread delay slot */
        func_00238060();
        D_0036DC98 = func_00182FB8();
        n = D_0036DCA8;
        func_00196050(D_0036DC98, 0);
        if (D_00467B00 == 3 && (D_0036DBEC >> 1) & 1) {
            CopyAqw__FPvT0i((char *)D_0036C680 + 0x60, D_0036E3D0, 10);
            CopyAqw__FPvT0i((char *)D_0036C680 + 0x100, D_0036E470, 9);
        }
        func_00293920(0);
        func_00195760(D_0036BD3C, D_0036C680->x24);
        if ((D_0036DBE0.xC >> 1) & 1 && D_00467B00 == 3 && (D_0036C680->grf & 8)) {
            int i;
            CopyAqw__FPvT0i((char *)D_0036C680 + 0x60, D_0036E500, 10);
            CopyAqw__FPvT0i((char *)D_0036C680 + 0x100, D_0036E5A0, 9);
            for (i = 0; i < D_00475480.cso; i++)
                func_00167DD8(D_00475480.apso[i], D_0036C680);
            func_00293920(0);
            func_00195760(D_0036BD3C, D_0036C680->x24);
        }
        func_00195760(D_0036BD40, D_0036C680->x4);
        } while (0);
        if (D_0036C680->grf & 1)
            func_001837E0();
        sceDmaSync(D_0036BD3C, 0, 0);
        func_002936C0(D_0036C688);
        if (D_0036C680->grf & 2) {
            if (D_0036DCA8 == n && D_0036DBE0.x0)
                func_00195688();
            func_001956B8();
            func_00183038(n);
        }
    }
}
