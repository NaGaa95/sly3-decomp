// SLY3_CFLAGS: -Os -G0
// 989snd EE-side init (Sly 2 counterpart: sly2-decomp src/hand/func_002319E8.c, there -O2): sets the command/return
// buffer pointers, binds the two SIF RPC servers (0x123456, 0x123457) with a 9999-iteration busy wait, then sends the
// init command. The nops in the loops are the compiler's r5900 short-loop padding, not asm.
typedef struct CB { void (*fn)(int, long); int pad; long arg; } CB;
typedef struct RPC { int x[16]; } RPC;
extern int *D_0034A280[2];
extern int D_0034A288[2];
extern CB *D_0034A290[2];
extern int *D_0034A298[2];
extern int D_0034A2A8, D_0034A2D8;
extern CB D_0034A2B0;
extern int D_004C4500[], D_004C5500[], D_004C8500[], D_004C8940[];
extern CB D_004C6500[], D_004C7500[];
extern RPC D_004C4180, D_004C8DC0;
extern int D_004C8D80[];
extern unsigned int D_004C8E00;
extern char D_0032A0F0[], D_0032A118[];
void func_00271388(const char *, ...);
void func_002956E0(int);
int func_00295D28(void *, int, int);
int func_00291290(int, int, void *);

void func_002906B8(int flags)
{
    int i;
    int buf[2];

    D_0034A280[0] = D_004C4500;
    D_0034A280[1] = D_004C5500;
    D_0034A298[0] = D_004C8500;
    D_0034A298[1] = D_004C8940;
    D_0034A290[0] = D_004C6500;
    D_0034A290[1] = D_004C7500;
    if (flags & 2)
        D_0034A2D8 = 1;
    else
        D_0034A2D8 = 0;
    func_002956E0(0);
    do {
        if (func_00295D28(&D_004C4180, 0x123456, 0) < 0) {
            func_00271388(D_0032A0F0, D_0032A118, 0xB5);
            while (1)
                ;
        }
        i = 9999;
        while (i--)
            ;
    } while (!D_004C4180.x[9]);
    D_0034A2A8 = 0;
    D_0034A2B0.fn = 0;
    D_0034A2B0.arg = 0;
    D_004C8E00 = 0;
    do {
        if (func_00295D28(&D_004C8DC0, 0x123457, 0) < 0) {
            func_00271388(D_0032A0F0, D_0032A118, 0xCA);
            while (1)
                ;
        }
        i = 9999;
        while (i--)
            ;
    } while (!D_004C8DC0.x[9]);
    ((volatile int *)D_004C8D80)[0] = 0;
    ((volatile int *)D_004C8D80)[4] = 0;
    *D_004C4500 = 0;
    *D_004C5500 = 0;
    D_0034A288[0] = 0xFFC;
    buf[0] = (int)D_004C8D80;
    buf[1] = flags;
    D_0034A288[1] = 0xFFC;
    func_00291290(0, 8, buf);
}
