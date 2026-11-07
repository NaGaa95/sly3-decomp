// Sly 2 counterparts: sceCdDiskReady_old + sceCdDiskReady_2425F0 (one unit: they share string literals)
// Sly 2 counterpart: sceCdDiskReady_old (decomp src/lib/sceCdDiskReady_old.c)
// (Claude agent) libcdvd func_002A09D0: bind retry loop sets the bound flag before break; both failure exits written out (gcc cross-jumps them).
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { int pad[9]; void *serve; int pad2[6]; } sceSifClientData;
extern int D_0034C390;
extern int D_0034C3C0;
extern volatile int D_0034C3AC;
extern int D_0034C3D0;
extern sceSifClientData D_004D0E90;
extern int D_004D0ED0[];
extern int D_0034D580[];
extern volatile int D_0034C3B0;
extern int D_0034DE00[];
int func_002955E0(const char *fmt, ...);
int func_002980D0(void);
int func_00298120(void);
void func_002A0028(void);
int func_002936F0(int);
int func_002A0520(int);
void func_002956E0(int);
int func_00295D28(sceSifClientData *, unsigned int, int);
void func_00299DF0(void *, int);
int func_00295F08(void *cd, int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize, void *end, void *earg);
int func_002936C0(int);

static __inline__ void nopdelay(void)
{
    int i = 0x100000;
    while (i--) ;
}
int func_002A09D0(int mode)
{
    int r;
    if (D_0034C390 > 0) func_002955E0("OLD DiskReady Call\n");
    r = func_002980D0();
    D_0034C3C0 = 1;
    if (r) func_00298120();
    func_002A0028();
    if (D_0034C3AC != func_002936F0(D_0034C3AC)) return 6;
    if (func_002A0520(1)) {
        func_002936C0(D_0034C3AC);
        if (mode == 8) return -1;
        return 6;
    }
    func_002956E0(0);
    if (D_0034C3D0 < 0) {
        while (1) {
            if (func_00295D28(&D_004D0E90, 0x8000059A, 0) < 0) {
                if (D_0034C390 > 0) func_002955E0("Libcdvd bind err CdDiskReady\n");
                nopdelay();
                continue;
            }
            if (D_004D0E90.serve != 0) { D_0034C3D0 = 0; break; }
            nopdelay();
        }
    }
    D_004D0ED0[0] = mode;
    func_00299DF0(D_004D0ED0, 4);
    if (func_00295F08(&D_004D0E90, 0, 0, D_004D0ED0, 4, D_0034D580, 4, 0, 0) < 0) {
        func_002936C0(D_0034C3AC);
        if (mode == 8) return -1;
        return 6;
    }
    if (D_0034C390 > 0) func_002955E0("DiskReady ended\n");
    r = *(int *)((unsigned int)D_0034D580 | 0x20000000);
    func_002936C0(D_0034C3AC);
    return r;
}

int func_002A0BE8(int mode)
{
    int r;
    int cnt;
    int i;
    if (D_0034C390 > 0) func_002955E0("NEW DiskReady Call\n");
    func_002A0028();
    if (D_0034C3B0 != func_002936F0(D_0034C3B0)) {
        if (mode == 8) return -1;
        return 6;
    }
    func_002956E0(0);
    cnt = 0;
    if (D_0034C3D0 < 0) {
        while (1) {
            if (func_00295D28(&D_004D0E90, 0x8000059C, 0) < 0) {
                if (D_0034C390 > 0) func_002955E0("Libcdvd bind err CdDiskReady\n");
                i = 0x100000; while (i--) ;
                continue;
            }
            if (D_004D0E90.serve != 0) { D_0034C3D0 = 0; break; }
            if (cnt > 0x10) {
                func_002936C0(D_0034C3B0);
                return func_002A09D0(mode);
            }
            i = 0x100000; while (i--) ;
            cnt++;
        }
    }
    r = func_002980D0();
    D_0034C3C0 = 0;
    if (r) func_00298120();
    D_004D0ED0[0] = mode;
    func_00299DF0(D_004D0ED0, 4);
    if (func_00295F08(&D_004D0E90, 0, 0, D_004D0ED0, 4, D_0034DE00, 4, 0, 0) < 0) {
        func_002936C0(D_0034C3B0);
        if (mode == 8) return -1;
        return 6;
    }
    if (D_0034C390 > 0) func_002955E0("DiskReady ended\n");
    r = *(int *)((unsigned int)D_0034DE00 | 0x20000000);
    func_002936C0(D_0034C3B0);
    return r;
}
