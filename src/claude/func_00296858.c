// Sly 2 counterpart: sceFsInit (decomp src/lib/sceFsInit.c)
// func_00296858: MATCH. -fstrict-aliasing is what fixes the prologue: flag (int) and next (pointer) get different alias
// sets, so the two stores before func_002980D0 are independent and the s0 save/lui chain outranks the s1 save in sched2.
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0 -fstrict-aliasing
// SLY3_ASM: gnu-reorder-db
typedef struct { int pad[9]; void *serve; } ClientData;
typedef struct { char c[4]; } B4;
struct iob { int fd, busy, x8, xC; };
struct FsPoffData { int flag; void *next; };
extern struct FsPoffData D_004CC780;
extern char D_004CC740[];
extern ClientData D_004CC700;
extern int D_0034A6A8;
extern struct iob D_004CC500[32];
extern void *D_004CAFC0[2];
extern char D_004CBC80[];
extern B4 D_004CBC40[2];
extern B4 D_004CC728;
extern int D_0034A69C;
extern int D_0034A6A0;
void func_002956E0(int);
int func_002980D0(void);
int func_00298120(void);
void *func_00299A28(unsigned int, void *, void *);
void func_002963C0(void *);
void func_00296810(void *);
int func_00295D28(ClientData *, unsigned int, unsigned int);
void func_00296160(void);
int func_002936E0(int);
int func_002936C0(int);
int func_00296260(void *, int, int, void *, int, void *, int, void *, void *, int);
int func_00296858(void)
{
    int oldei, i;
    struct iob *io;
    B4 tmp;
    struct FsPoffData *p = &D_004CC780;
    func_002956E0(0);
    D_004CC780.flag = 0;
    p->next = 0;
    oldei = func_002980D0();
    func_00299A28(0x80000011, func_002963C0, D_004CC740);
    func_00299A28(0x80000013, func_00296810, p);
    if (oldei) func_00298120();
    while (1) {
        if (func_00295D28(&D_004CC700, 0x80000001, 0) < 0)
            return -22;
        if (D_004CC700.serve != 0)
            break;
        i = 0x100000;
        do __asm__ volatile(""); while (i-- != 0);
    }
    func_00296160();
    func_002936E0(D_0034A6A8);
    for (io = D_004CC500; io < &D_004CC500[32]; io++)
        { __asm__ volatile(""); io->busy = 0; }
    func_002936C0(D_0034A6A8);
    D_004CAFC0[0] = D_004CBC80;
    D_004CAFC0[1] = D_004CBC80 + 0x440;
    if (func_00296260(&D_004CC700, 0xFF, 0, D_004CAFC0, 8, D_004CBC40, 8, 0, 0, 0) < 0)
        return 0xFFFEFFFF;
    D_004CC728 = *(B4 *)((unsigned int)&D_004CBC40[0] | 0x20000000);
    tmp = *(B4 *)((unsigned int)&D_004CBC40[1] | 0x20000000);
    D_0034A6A0 = *(int *)&tmp == 2;
    D_0034A69C = 1;
    return 0;
}
