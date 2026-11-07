// Sly 2 counterpart: sceCdInit (decomp src/lib/sceCdInit.c)
// func_002A06E8 (T1576): MATCH. Keys: the bind-ok path sits inside the while(1) loop and stores 6798 = 0 BEFORE the mode
// (its hi register then has a shorter live length, so global-alloc gives hi(6798) s4 and hi(679C) s5); the init-counter
// increment is a volatile store of a plain read (the read must not depend on the volatile 6764 store); init store order
// found by an exhaustive/hill-climb search (sched1 order), checked against the relocation symbols too.
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { int pad[9]; void *serve; int pad2[6]; } sceSifClientData;
extern int D_0034C390;
extern volatile int D_0034C3A0;
extern volatile int D_0034C3A4;
extern volatile int D_0034C3A8;
extern volatile int D_0034C3AC;
extern int D_0034C3B8;
extern int D_0034C3BC;
extern int D_0034C3C4;
extern int D_0034C3C8;
extern int D_0034C3CC;
extern int D_0034C3D0;
extern int D_0034C3D4;
extern int D_0034C3D8;
extern int D_0034C3DC;
extern sceSifClientData D_004D0E68;
extern int D_004D0EC0[];
extern int D_0034D580[];
extern char D_0032B6C0[];   // "Libcdvd bind err %d CD_Init %d\n"
extern char D_0032B6E0[];   // "Libcdvd Exit\n"
int func_002955E0(const char *, ...);
int func_002A0520(int);
void func_002956E0(unsigned int);
int func_00295D28(sceSifClientData *, unsigned int, unsigned int);
void func_00299DF0(void *, int);
int func_00295F08(sceSifClientData *, int, unsigned int, void *, int, void *, int, void *, void *);
void func_002A0110(void);
void func_002A0028(void);
int func_002A0208(void);

static __inline__ void nopdelay(void)
{
    int i = 0x100000;
    while (i--) ;
}

int func_002A06E8(int mode)
{
    int r;
    int *p;
    if (func_002A0520(1)) return 0;
    func_002956E0(0);
    D_0034C3CC = -1;
    D_0034C3BC = -1;
    D_0034C3D4 = -1;
    D_0034C3D0 = -1;
    D_0034C3D8 = -1;
    D_0034C3C8 = -1;
    D_0034C3A4 = 1;
    D_0034C3B8 = 0;
    *(volatile int *)&D_0034C3DC = D_0034C3DC + 1;
    while (1) {
        int b = func_00295D28(&D_004D0E68, 0x80000592, 0);
        if (b < 0) {
            if (D_0034C390 > 0) func_002955E0(D_0032B6C0, b, D_0034C3DC);
            nopdelay();
            continue;
        }
        if (D_004D0E68.serve != 0) {
            D_0034C3D8 = 0;
            D_004D0EC0[0] = mode;
            func_00299DF0(D_004D0EC0, 4);
            p = D_0034D580;
            if (func_00295F08(&D_004D0E68, 0, 0, D_004D0EC0, 4, p, 0x10, 0, 0) < 0) {
                D_0034C3A4 = 0;
                return 0;
            }
            break;
        }
        nopdelay();
    }
    {
        // reply words read through the uncached mirror
        int b = *(int *)((unsigned int)&p[1] | 0x20000000);
        int c = *(int *)((unsigned int)&p[2] | 0x20000000);
        int a = *(int *)((unsigned int)&p[3] | 0x20000000);
        r = 1;
        if (a == 0xFF) {
        } else if (a == 0xFE) {
            D_0034C390 = 1;
        } else if (b / 256 < 2 || c / 256 < 2) {
            r = 2;
        }
    }
    D_0034C3A4 = 0;
    switch (mode) {
    case 5:
        if (D_0034C390 > 0) func_002955E0(D_0032B6E0);
        func_002A0110();
        D_0034C3A8 = -1;
        D_0034C3AC = -1;
        D_0034C3A0 = -1;
        D_0034C3C4 = 0;
        break;
    case 0: case 1:
    default:
        func_002A0028();
        func_002A0208();
        D_0034C3C4 = 1;
        break;
    }
    return r;
}
