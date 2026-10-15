// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct X { char pad[0x18]; float af[4]; };
void func_00165570(struct X *p);
void func_00165548(struct X *p, int i, float f)
{
    p->af[i] = f;
    func_00165570(p);
}
