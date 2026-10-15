// Reference: Sly 2 src/lib/sceSifSyncIop.c; target Sly 3 0x00297F70.
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
int sceSifGetReg(int);
void sceSifSetReg(int, int);
void func_00299648(void);
int sceSifSyncIop(void)
{
    if (!(sceSifGetReg(4) & 0x40000)) return 0;
    func_00299648();
    sceSifSetReg(1, 1);
    sceSifSetReg(0, 1);
    return 1;
}
