// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// PsndStartDialog (SafeHouse name, 0x2485D8). Sly 3 version of the Sly 2 src/hand/func_001FE5F0.cpp: takes an explicit object (4th arg) and fills 7 slots.
struct X { char pad[0xC]; virtual void v0(); };
struct Ref;
extern "C" void func_002BF360(Ref *, X *);
struct Ref {
    X *px;
    Ref &operator=(X *p) { func_002BF360(this, p); return *this; }
    operator X *() { return px; }
};
struct D { char pad[0x48]; int n48; char pad2[0x54 - 0x4C]; int n54; };
struct P { char pad[0x210]; Ref r210; char pad2[0x23C - 0x214]; X *a[7]; int n258; int n25C; int n260; };
struct G;
extern G D_00475480;
extern char D_004BC220[];
extern "C" {
void func_00248740(P *);   /* StopDialog */
D *func_00246E10(P *, int);
X *func_00245FE8(D *, int);
void func_0027ECB0(void *, int, int);
X *func_0017E5D8(G *, int, int, int);
int func_00246F30(P *, int);
X *func_0023FB68(X *, int);
}
extern "C" X *func_002485D8(P *p, int k, int f, X *po)
{
    D *pd;
    func_00248740(p);
    pd = func_00246E10(p, k);
    if (!pd) { __asm__("" : : "r"(p)); /* zero-insn: raises p's allocation priority (s0) */ return 0; }
    p->r210 = func_00245FE8(pd, 0);
    p->n258 = 0;
    p->n25C = 0;
    p->n260 = 0;
    if (!f) func_0027ECB0(D_004BC220, k, pd->n48);
    if (pd->n54) {
        if (!po && pd->n48 != -1)
            po = func_0017E5D8(&D_00475480, 0x105, pd->n48, 0);
        if (po) {
            int i;
            for (i = 0; i < 7; i++) {
                if (i == 3) p->a[3] = po;
                else if (i == 6) p->a[6] = 0;
                else p->a[i] = func_0023FB68(po, func_00246F30(p, i));
                if (p->a[i]) p->a[i]->v0();
            }
        }
    }
    return p->r210;
}
