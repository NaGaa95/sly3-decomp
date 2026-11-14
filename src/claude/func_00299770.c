// Sly 2 counterpart: sceSifInitCmd (decomp src/lib/sceSifInitCmd.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
/* func_00299770 (libkernel sifcmd). Handler func field must be a function pointer type. */
typedef struct { void (*func)(void *, void *); void *data; int pad; } HANDLER;
typedef struct {
    void *pktbuf;
    void *unused;
    void *iopbuf;
    HANDLER *sys;
    int nsys;
    HANDLER *usr;
    int nusr;
    int *sreg;
} CMDDATA;
typedef struct { unsigned int size; void *dest; int cid; unsigned int opt; void *buf; } CAPKT;

extern int D_0034B680;
extern unsigned char D_004CF680[0x80];
extern unsigned char D_004CF700[0x40];
extern CAPKT D_004CF740;
extern int D_004CF754;
extern CMDDATA D_004CF758;
extern HANDLER D_004CF780[32];
extern int D_004CF900[32];

int func_002980D0(void);
void func_00298120(void);
void func_00293920(int);
void func_00293A80(void);
int func_002933B0(int, void *, int);
int func_00293EC8(int);
unsigned int sceSifGetReg(unsigned int);
unsigned int func_00293AA0(unsigned int, unsigned int);
void func_00299C28(unsigned int, void *, unsigned int, void *, void *, unsigned int);
void func_00299738(void *, void *);
void func_00299718(void *, void *);
void func_00299CA8(void);

void func_00299770(void)
{
    int i;

    func_002980D0();
    if (D_0034B680) {
        func_00298120();
        return;
    }
    D_0034B680 = 1;
    D_004CF758.pktbuf = (void *)((unsigned int)D_004CF680 | 0x20000000);
    D_004CF758.unused = (void *)((unsigned int)D_004CF700 | 0x20000000);
    D_004CF758.iopbuf = 0;
    D_004CF758.sys = D_004CF780;
    D_004CF758.nsys = 32;
    D_004CF758.usr = 0;
    D_004CF758.nusr = 0;
    D_004CF758.sreg = D_004CF900;
    for (i = 0; i < 32; i++) {
        D_004CF780[i].func = 0;
        D_004CF780[i].data = 0;
    }
    for (i = 0; i < 32; i++)
        D_004CF900[i] = 0;
    D_004CF780[0].func = func_00299738;
    D_004CF780[0].data = &D_004CF758;
    D_004CF780[1].func = func_00299718;
    D_004CF780[1].data = &D_004CF758;
    func_00298120();
    func_00293920(0);
    if (*(volatile unsigned int *)0x1000E010 & 0x20)
        *(volatile unsigned int *)0x1000E010 = 0x20;
    if (!(*(volatile unsigned int *)0x1000C000 & 0x100))
        func_00293A80();
    D_004CF754 = func_002933B0(5, (void *)func_00299CA8, 0);
    func_00293EC8(5);
    D_004CF758.iopbuf = (void *)sceSifGetReg(0x80000000);
    if (D_004CF758.iopbuf) {
        D_004CF740.buf = D_004CF680;
        func_00299C28(0x80000000, &D_004CF740, 0x14, 0, 0, 0);
        return;
    }
    {
        while (!(sceSifGetReg(4) & 0x20000))
            ;
        D_004CF758.iopbuf = (void *)sceSifGetReg(2);
        func_00293AA0(0x80000000, (unsigned int)D_004CF758.iopbuf);
        func_00293AA0(0x80000001, (unsigned int)&D_004CF758);
        D_004CF740.buf = D_004CF680;
        D_004CF740.opt = 0;
        func_00299C28(0x80000002, &D_004CF740, 0x14, 0, 0, 0);
    }
}
