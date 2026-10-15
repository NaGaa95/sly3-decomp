// Reconstructed from matching Sly 2 code with Sly 3 calls and data addresses.
struct A { char pad[0xA0]; int f; };
void func_00246DF8(void);
void func_00291D30(int id, int n, int a, int b, int c, int d, int e, void (*pfn)(void), long p);
void func_00247B38(struct A *p)
{
    if (!p->f) {
        p->f = 1;
        func_00291D30(0x524B5553, 0xC, 0, 0, 0, 0, 0, func_00246DF8, (long)p);
    }
}
