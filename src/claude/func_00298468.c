// Sly 2 counterpart: InitExecPS2 (decomp src/lib/InitExecPS2.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { int num; void *func; } SysEnt;
extern SysEnt D_0034AE88[];
extern char D_0034A6E0[];
int func_00298400(void);
void func_00298398(int, void *);
void func_002983A8(void *, void *, int);
void func_00293920(int);
void *func_002983F0(int);
void func_00298468(void)
{
    SysEnt *t;
    unsigned int i;
    if (func_00298400()) {
        t = D_0034AE88;
        func_00298398(t[0].num, t[0].func);
        func_002983A8((void *)0x80074000, D_0034A6E0, 0x7A8);
        func_00293920(0);
        func_00293920(2);
        func_00298398(t[1].num, t[1].func);
        for (i = 2; i < 3; i++)
            func_00298398(t[i].num, func_002983F0(t[i].num));
    }
}
