// Sly 2 counterpart: mceGetInfoApdx (decomp src/lib/mceGetInfoApdx.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
extern int *D_004D1228;
extern int *D_004D122C;
extern int *D_004D1230;
extern int D_0034DF98;
int func_002936D0(int);
void func_002A2B10(void *data)
{
    int *p = (int *)((unsigned int)data | 0x20000000);
    if (D_004D1228) *D_004D1228 = p[0];
    if (D_004D122C) *D_004D122C = p[1];
    if (D_004D1230) *D_004D1230 = p[0x24];
    func_002936D0(D_0034DF98);
}
