// Sly 2 counterpart: sceSifResetIop (decomp src/lib/sceSifResetIop.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct {
    unsigned int psize:8;
    unsigned int dsize:24;
    unsigned int dest;
    int cid;
    unsigned int opt;
} SifCmdHeader;
typedef struct {
    SifCmdHeader hdr;
    int size;
    int flag;
    char arg[80];
} SifCmdResetData;
typedef struct {
    void *src;
    void *dest;
    int size;
    int attr;
} SifDmaTransfer;
extern SifCmdResetData D_004CCC00 __attribute__((aligned(64)));
void sceSifSetReg(int, int);
void func_00293970(void);
unsigned int sceSifGetReg(unsigned int);
unsigned int func_00293AA0(unsigned int, unsigned int);
void func_00299DF0(void *, int);
unsigned int func_00293A60(SifDmaTransfer *, int);
int func_00297E18(const char *arg, int mode)
{
    SifDmaTransfer dmat;
    void *dest;
    int i;

    sceSifSetReg(0, 0);
    sceSifSetReg(1, 0);
    func_00293970();
    dest = (void *)sceSifGetReg(0x80000000);
    D_004CCC00.flag = mode;
    for (i = 0; arg[i] != 0; i++)
        D_004CCC00.arg[i] = arg[i];
    D_004CCC00.hdr.dest = 0;
    D_004CCC00.hdr.dsize = 0;
    D_004CCC00.size = i;
    D_004CCC00.hdr.cid = 0x80000003;
    D_004CCC00.hdr.psize = sizeof(SifCmdResetData);
    dmat.src = &D_004CCC00;
    dmat.dest = dest;
    dmat.size = sizeof(SifCmdResetData);
    dmat.attr = 0x44;
    func_00299DF0(&D_004CCC00, sizeof(SifCmdResetData));
    func_00293AA0(4, 0x40000);
    if (func_00293A60(&dmat, 1) != 0) {
        func_00293AA0(4, 0x10000);
        func_00293AA0(4, 0x20000);
        func_00293AA0(0x80000002, 0);
        func_00293AA0(0x80000000, 0);
        return 1;
    }
    return 0;
}

