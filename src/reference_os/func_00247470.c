// Sly 2 reference: src/hand/func_001FD5E8.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
struct K { int n0; int n4; int n8; char bC; char pad[0x110 - 0xD]; };
struct X { int n0; int n4; char pad[0x34 - 8]; int n34; int n38; int n3C; };
struct P { char pad[0xA8]; struct X xA8; char pad2[0xE8 - 0xA8 - sizeof(struct X)]; int pE8; char pad3[0xF8 - 0xEC]; int nF8; int *aFC; };
void func_002BC568(struct K *);
int func_00290C70(int, int);
void func_00290E38(void);
int func_00290F50(int, int);
static inline int FSet(struct K *pk, struct X *px)
{
    if (!px) return 0;
    {
        int a = px->n34;
        int c = px->n0;
        int d = px->n3C;
        int b = px->n4;
        pk->n8 = 2;
        pk->n4 = b ^ d;
        pk->n0 = (c ^ a) + 0xCA0;
    }
    return pk->n4 != 0;
}
void func_00247470(struct P *p)
{
    int i;
    if (!p->pE8) {
        struct K k;
        k.n8 = 2;
        func_002BC568(&k);
        if (FSet(&k, &p->xA8) && k.n8 == 2) p->pE8 = func_00290C70(k.n0, 0);
        func_00290E38();
    }
    for (i = 0; i < p->nF8; i++) {
        if (p->aFC[i] == 2) continue;
        if (func_00290F50(p->pE8, i)) p->aFC[i] = 2;
    }
}
