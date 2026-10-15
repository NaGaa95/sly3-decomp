// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct S { int f0; int f4; char pad[0x28]; char x30[0x20]; char x50[0x20]; char x70[0x10]; };
void func_00291B88(void);
void func_0014EF78(void *p);
void func_001DAC88(void *p);
void func_001DB308(struct S *p)
{
    if (p->f0) {
        func_00291B88();
        p->f0 = 1;
        p->f4 = -1;
        func_0014EF78(p->x30);
        func_0014EF78(p->x50);
        func_001DAC88(p->x70);
    }
}
