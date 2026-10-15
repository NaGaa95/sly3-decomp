// Sly 2 reference: src/lib/sceSifExitCmd.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -O2 -G0
int func_00293E60(int);
int func_002933D0(int, int);
extern int D_004CF754; extern int D_0034B680;
void func_002999F0(void)
{
    func_00293E60(5);
    func_002933D0(5, D_004CF754);
    D_0034B680 = 0;
}
