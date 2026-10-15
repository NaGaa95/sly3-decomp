// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct P { char pad[0x24]; void *p24; char pad2[0x30 - 0x28]; int n30; int n34; int n38; char pad3[0x48 - 0x3C]; int n48; };
int func_00239CC0(struct P *);
int func_00239A78(void *, int);
int func_0023A210(void *, int, int, int, int);
void func_00239CE8(struct P *, int);
void func_00239DB8(struct P *p, int n)
{
    if (!func_00239CC0(p) && n != -1) {
        int r = func_00239A78(p->p24, n);
        if (r != -1 && func_0023A210(p->p24, p->n48, !p->n30 ? p->n34 : p->n38, r, 0))
            func_00239CE8(p, n);
    }
}
