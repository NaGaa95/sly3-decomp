// Sly 2 counterpart: _sceCd_ncmd_prechk (decomp src/lib/_sceCd_ncmd_prechk.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { char p[0x24]; int server; } RpcCD;
extern RpcCD D_0034D550;
extern volatile int D_0034C3A8;
extern int D_0034C390;
extern int D_0034C39C;
extern int D_0034C3BC;
extern char D_0032B620[];
extern char D_0032B648[];
void func_002A0028(void);
int func_002936F0(int);
int func_002936C0(int);
int func_002955E0(const char *, ...);
int sceCdSync(int);
void func_002956E0(int);
int func_00295D28(void *, unsigned int, int);
static __inline__ void nopdelay(void)
{
    int i = 0x100000;
    while (i--) ;
}
int func_002A0290(int cmd)
{
    int i;
    func_002A0028();
    if (D_0034C3A8 != func_002936F0(D_0034C3A8)) {
        if (D_0034C390 > 0) func_002955E0(D_0032B620, cmd, D_0034C39C);
        return 0;
    }
    D_0034C39C = cmd;
    if (sceCdSync(1)) {
        func_002936C0(D_0034C3A8);
        return 0;
    }
    func_002956E0(0);
    if (D_0034C3BC < 0) {
        while (1) {
            if (func_00295D28(&D_0034D550, 0x80000595, 0) < 0) {
                if (D_0034C390 > 0) func_002955E0(D_0032B648);
                nopdelay();
                continue;
            }
            if (D_0034D550.server != 0) break;
            nopdelay();
        }
        D_0034C3BC = 0;
    }
    return 1;
}
