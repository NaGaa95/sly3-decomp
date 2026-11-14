// Sly 2 counterpart: InitAlarm (decomp src/lib/InitAlarm.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { int num; void *func; } SysEnt;
extern SysEnt D_0034B610[];
extern char D_0034AEA8[];
extern char D_0034B5E8[];
void func_00298580(int, void *);
void func_00298590(void *, void *, int);
void func_00293920(int);
void *func_002985D8(int);
void func_002985E8(void)
{
    SysEnt *t;
    unsigned int i;
    if (!(*(volatile int *)0x10001810 & 0x100)) {
        t = D_0034B610;
        func_00298580(t[0].num, t[0].func);
        func_00298590((void *)0x80076000, D_0034AEA8, 0x740);
        func_00298590((void *)0x82000, D_0034B5E8, 0x28);
        func_00293920(0);
        func_00293920(2);
        func_00298580(t[1].num, t[1].func);
        for (i = 2; i < 8; i++)
            func_00298580(t[i].num, func_002985D8(t[i].num));
    }
}
