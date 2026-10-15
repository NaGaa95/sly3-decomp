// Reference algorithm: src/hand/func_001ED960.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct E { int a; void *pv; int b; void *powner; int dle; };
struct P { char pad[0x24]; int x24; char pad2[0x38 - 0x28]; int dl; };
extern int D_0046FF40;
extern struct E D_0046FF48[];
void func_0011AD68(int *pdle);
void func_0011ADA8(int *pdl, struct E *pe);
void func_0027E420(void *a, int b, int c, void *d, struct E *pe, int *pb);
void func_00235D50(struct E *pe);
int func_00237060(struct P *p, void *a1, void *a2)
{
    struct E e;
    struct E *pe;
    if (D_0046FF40 < 0x400) {
        pe = &D_0046FF48[D_0046FF40++];
        func_0011AD68(&pe->dle);
        func_0011ADA8(&p->dl, pe);
        pe->powner = p;
    } else {
        pe = &e;
    }
    func_0027E420(a2, 0xD, 1, a1, pe, &pe->b);
    pe->pv = &p->x24;
    func_00235D50(pe);
    return 1;
}
