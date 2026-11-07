// Sly 2 counterpart: sceIpuInit (decomp src/lib/sceIpuInit.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef int qword __attribute__((mode(TI)));
#define REG(a) (*(volatile unsigned int *)(a))
#define FIFO (*(volatile qword *)0x10007010)
extern volatile qword D_0034E190[5];
extern qword D_0034E1E0[2];
void func_002B3658(int);
#define SYNC() while ((int)REG(0x10002010) < 0)
void func_002B36D0(void)
{
    func_002B3658(1);
    REG(0x10002010) = 0x40000000;
    SYNC();
    REG(0x10002000) = 0;
    SYNC();
    FIFO = D_0034E190[0];
    FIFO = D_0034E190[1];
    FIFO = D_0034E190[2];
    FIFO = D_0034E190[3];
    FIFO = D_0034E190[4];
    FIFO = D_0034E190[4];
    FIFO = D_0034E190[4];
    FIFO = D_0034E190[4];
    REG(0x10002000) = 0x50000000;
    SYNC();
    REG(0x10002000) = 0x58000000;
    SYNC();
    FIFO = D_0034E1E0[0];
    FIFO = D_0034E1E0[1];
    REG(0x10002000) = 0x60000000;
    SYNC();
    REG(0x10002000) = 0x90000000;
    SYNC();
    REG(0x10002010) = 0x40000000;
    SYNC();
    REG(0x10002000) = 0;
    SYNC();
}
