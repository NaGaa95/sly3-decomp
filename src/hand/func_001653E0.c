// Reconstructed from matching Sly 2 code with Sly 3 calls and data addresses.
struct CLK { char pad[0x18]; float af[9]; };
extern struct CLK D_0036BB98;
void func_00165570(void *p);
void func_001653E0(int *p)
{
    *p = 0;
    D_0036BB98.af[0] = 1.0f;
    D_0036BB98.af[1] = 1.0f;
    D_0036BB98.af[2] = 1.0f;
    D_0036BB98.af[5] = 1.0f;
    D_0036BB98.af[6] = 1.0f;
    D_0036BB98.af[8] = 1.0f;
    D_0036BB98.af[7] = 1.0f;
    D_0036BB98.af[4] = 1.0f;
    func_00165570(p);
}
