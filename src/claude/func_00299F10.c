// Sly 2 counterpart: InitTLBFunctions (decomp src/lib/InitTLBFunctions.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { int no; void *fn; } ENT;
extern ENT D_0034BA08[8];
extern int D_0034BA00;
extern char D_0034B688[];
void func_00299F00(int, void *);
void *func_00299EF0(int);
void func_00299EA8(void *, void *, int);
void func_00293920(int);
void func_00299F10(void)
{
    unsigned int i;
    func_00299F00(D_0034BA08[0].no, D_0034BA08[0].fn);
    func_00299EA8((void *)0x80075000, D_0034B688, 0x330);
    func_00293920(0);
    func_00293920(2);
    func_00299F00(D_0034BA08[1].no, D_0034BA08[1].fn);
    func_00299F00(D_0034BA08[2].no, D_0034BA08[2].fn);
    for (i = 3; i < 8; i++)
        func_00299F00(D_0034BA08[i].no, func_00299EF0(D_0034BA08[i].no));
    D_0034BA00 = (int)func_00299EF0(3);
}
